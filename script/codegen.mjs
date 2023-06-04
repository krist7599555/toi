import * as fs from "node:fs/promises";
import * as path from "node:path";
import { pipe } from "@krist7599555/lodosh";
import { arr_map } from "@krist7599555/lodosh";
import { async_pipe } from "ts-async-pipe";
import * as csv from "csv/sync";
import * as yaml from "yaml";
import { sort_by } from "@krist7599555/lodosh";
import { group_by } from "@krist7599555/lodosh";
import { record_values } from "@krist7599555/lodosh";
import { arr_filter } from "@krist7599555/lodosh";
import { is_match } from "@krist7599555/lodosh";
import { group_by_with } from "@krist7599555/lodosh";
import { codegen_replace_block } from "./codegen_utils.mjs";
const root_dir = new URL("../", import.meta.url);

const tasks = await async_pipe(
  fs.readFile(new URL("./meta_problem.csv", root_dir)),
  (buf) => csv.parse(buf, { columns: true }),
  sort_by((it) => [
    ["desc", +it.year.replace("toi", "")],
    ["asc", it.day],
    ["asc", "it.task"],
  ]),
  arr_map((it) => ({
    year: `${it.year}`,
    day: +it.day,
    problem_id: `${it.problem_id}`,
    problem_title: `${it.problem_title}`,
    image: `${it.image}` || null,
    problem_link:
      it.year == "toi19"
        ? "https://otog.cf/"
        : `https://beta.programming.in.th/tasks/${it.problem_id}`,
  }))
);

const tois = await async_pipe(
  fs.readFile(new URL("./meta_toi.yaml", root_dir), "utf-8"),
  (buf) => yaml.parse(buf),
  record_values,
  sort_by((it) => [["desc", it.order]]),
  arr_map((it) => {
    const year = `toi${it.order}`;
    return {
      year,
      logo: `${it.logo || ""}` || null,
      order: +it.order,
      description: `${it.description || ""}` || null,
      tasks: pipe(
        tasks,
        arr_filter(is_match({ year })),
        group_by((it) => it.day)
      ),
    };
  })
);

const WARN =
  "<!-- ! THIS IS AUTO GENERATE DOCS. CHANGE THIS WILL RESULT NOTHING -->";
const NO_IMAGE =
  "https://github.com/krist7599555/toi/assets/19445033/80c80822-7583-4bcd-a705-dae3eacdee85";

/**
 *
 * @param {typeof tois[number]} toi
 * @param {'#' | '##'} base
 * @returns string
 */
function md_single_toi(toi, base) {
  return `${WARN}
${base} ${toi.year.toUpperCase()}

<img width="500" alt="${toi.year} logo" src="${toi.logo || NO_IMAGE}">

${toi.description || ""}

${toi.tasks
  .map(
    ([day, tasks]) => `${WARN}\n${base}# ${toi.year.toUpperCase()} Day ${
      day > 0 ? day : "?"
    }

${tasks
  .map(
    (t) =>
      `- [${t.problem_id}](./${toi.year}/${t.problem_id}) - ${
        t.problem_title
      } [ลองทำ](${t.problem_link})\n\n  <img width="350" alt="${
        t.problem_id
      }" src="${t.image || NO_IMAGE}">`
  )
  .join("\n\n")
  .trim()}`
  )
  .join("\n\n")
  .trim()}`.replace(/\n\n+/gm, "\n\n");
}

{
  // /README.md
  const tois_str = pipe(
    tois,
    arr_map((toi) => md_single_toi(toi, "##")),
    (arr) => arr.join("\n\n").trim().replace(/\n\n+/gm, "\n\n")
  );
  await async_pipe(
    fs.readFile(new URL("./README.md", root_dir), "utf-8"),
    (str) => codegen_replace_block(str, "@codegen_tois", tois_str),
    (str) => fs.writeFile(new URL("./README.md", root_dir), str)
  );

  // /toixx/README.md
  for (const toi of tois) {
    const md_path = new URL(`./${toi.year}/README.md`, root_dir);
    await async_pipe(
      fs.readFile(md_path, "utf-8"),
      (str) =>
        codegen_replace_block(
          str,
          "@codegen_toi",
          pipe(md_single_toi(toi, "#"), (str) => {
            const lines = str.split("\n");
            const head_idx = lines.findIndex((it) => it.startsWith("# "));
            console.log({ head_idx, lines });
            lines.splice(head_idx + 1, 0, "", "[🏠 รวมเฉลยทุกปี](../)");
            return lines.join("\n");
          })
        ),
      (str) => fs.writeFile(md_path, str)
    );
  }
}
