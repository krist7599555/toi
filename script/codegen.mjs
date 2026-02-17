import { arr_filter_map, arr_map, is_match, pipe } from "@krist7599555/lodosh";
import { glob } from "glob";
import * as fs from "node:fs/promises";
import * as path from "node:path";
import { async_pipe } from "ts-async-pipe";

import {
  codegen_override_block,
  codegen_replace_block_string,
  string_insertline_after,
} from "./codegen_utils.mjs";

import * as ToiData from "./toi_data.mjs";

const root_dir = new URL("../", import.meta.url);

// INFORMATION
const problems = await ToiData.getProblemCsv();
const tois = await ToiData.getCompetitionYaml();

const MD_WARN_NO_EDIT =
  "<!-- ! THIS IS AUTO GENERATE DOCS. CHANGE THIS WILL RESULT NOTHING -->";
const URL_NO_IMAGE =
  "https://github.com/krist7599555/toi/assets/19445033/80c80822-7583-4bcd-a705-dae3eacdee85";

/**
 * Create Toi Markdown
 * @param {typeof tois[number]} toi
 * @param {'#' | '##'} base
 * @param {'./' | '../' | '../../'} rel_to_root
 * @returns string
 */
function toi_to_markdown(toi, base, rel_to_root) {
  return `${MD_WARN_NO_EDIT}
${base} [${toi.year.toUpperCase()}](${rel_to_root}${toi.year})

<img width="500" alt="${toi.year} logo" src="${toi.logo || URL_NO_IMAGE}">

${toi.description || ""}

${toi.tasks
  .map(
    ([
      day,
      tasks,
    ]) => `${MD_WARN_NO_EDIT}\n${base}# เฉลย ${toi.year.toUpperCase()} day ${
      day > 0 ? day : "?"
    }

${tasks
  .map(
    (t) =>
      `- [${t.problem_id}](${rel_to_root}${toi.year}/${t.problem_id}) - ${
        t.problem_title
      } [ลองทำ](${t.problem_link})\n\n  <img width="350" alt="${
        t.problem_id
      }" src="${t.image || URL_NO_IMAGE}">`
  )
  .join("\n\n")
  .trim()}`
  )
  .join("\n\n")
  .trim()}`.replace(/\n\n+/gm, "\n\n");
}

// SIDE EFFECT

async function codegen_root_readme() {
  // /README.md
  const tois_str = pipe(
    tois,
    arr_map((toi) => toi_to_markdown(toi, "##", "./")),
    (arr) => arr.join("\n\n").trim().replace(/\n\n+/gm, "\n\n")
  );
  await async_pipe(
    fs.readFile(new URL("./README.md", root_dir), "utf-8"),
    (str) => codegen_replace_block_string(str, "@codegen_tois", tois_str),
    (str) => fs.writeFile(new URL("./README.md", root_dir), str)
  );
}

async function codegen_competitions_readme() {
  // /toixx/README.md
  for (const toi of tois) {
    await codegen_override_block({
      file: new URL(`./${toi.year}/README.md`, root_dir),
      codegen_block: "@codegen_toi",
      replacer: () => {
        const md = toi_to_markdown(toi, "#", "../");
        const md_add_nav = string_insertline_after(
          md,
          (line) => line.startsWith("# "),
          ["", "[🏠 รวมเฉลยทุกปี](../)"]
        );
        return md_add_nav;
      },
    });
  }
}

async function codegen_problems_readme() {
  // toixx/toixx_taskname/README.md
  for (const task of problems) {
    const folder = new URL(`./${task.year}/${task.problem_id}`, root_dir);
    // prettier-ignore
    const readme = new URL(`./${task.year}/${task.problem_id}/README.md`, root_dir);
    await fs.access(folder).catch(() => fs.mkdir(folder));
    // prettier-ignore
    await fs.access(readme).catch(() => fs.writeFile(readme, "<!-- @codegen_problem begin -->\n<!-- @codegen_problem end -->\n"));
    {
      const md = await fs.readFile(readme, "utf-8");
      // prettier-ignore
      if (!md.includes("@codegen_problem")) {
        await fs.writeFile(readme, "<!-- @codegen_problem begin -->\n<!-- @codegen_problem end -->\n" + md);
      }
    }

    const files = await async_pipe(
      glob("*.{cpp,pdf}", {
        cwd: folder,
      }),
      arr_map((filename) => {
        return {
          ext: path.extname(filename),
          basename: path.basename(filename),
        };
      })
    );

    // prettier-ignore
    const o = {
      pdf: arr_filter_map(files, (it) => is_match(it, { ext: ".pdf" }) ? it.basename : null).map(f => `[💎 ${f.replace(task.problem_id, 'problem')}](./${f})\n`),
      cpp: arr_filter_map(files, (it) => is_match(it, { ext: ".cpp" }) ? it.basename : null).map(f => `[🎉 ${f.replace(task.problem_id, 'solution')}](./${f})\n`),
    };
    console.log(o);

    const problem = new URL(
      `./${task.year}/${task.problem_id}/${task.problem_id}.pdf`,
      root_dir
    );
    await fs.access(problem).catch(async (err) => {
      console.log("loading pdf");
      const res = await fetch(
        `https://beta-programming-in-th.s3-ap-southeast-1.amazonaws.com/statements/${task.problem_id}.pdf`
      );
      const buf = await res.arrayBuffer();
      await fs.writeFile(problem, Buffer.from(buf));
    });

    const md = await fs.readFile(readme, "utf-8");
    const new_md = codegen_replace_block_string(
      md,
      "@codegen_problem",
      `# ${task.year.toUpperCase()} ${task.problem_id.split("_")[1]} - ${
        task.problem_title
      }

[🏠 รวมเฉลย ${task.year.toUpperCase()}](../)

${[...o.pdf, ...o.cpp].join("\n")}

<img width="700" src="${task.image || URL_NO_IMAGE}" />
`.replace(/\n\n+/g, "\n\n")
    );
    await fs.writeFile(readme, new_md);
  }
}

// MAIN FUNCTION
async function codegen_all() {
  await codegen_root_readme();
  await codegen_competitions_readme();
  await codegen_problems_readme();
}
codegen_all();
