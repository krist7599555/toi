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

/** @type {{ year: `toi${number}`, day: string, task: string, problem_id: string, problem_title: string, image: string | null }[]} */
const tasks = await async_pipe(
  fs.readFile(new URL("./meta_problem.csv", root_dir)),
  (buf) => csv.parse(buf, { columns: true }),
  sort_by((it) => [
    ["desc", +it.year.replace("toi", "")],
    ["asc", it.day],
    ["asc", "it.task"],
  ])
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
      logo: it.logo,
      order: it.order,
      description: it.description,
      tasks: pipe(
        tasks,
        arr_filter(is_match({ year })),
        group_by_with(
          (it) => it.day,
          (arr) => arr
        )
      ),
    };
  })
);

const NO_IMAGE =
  "https://github.com/krist7599555/toi/assets/19445033/80c80822-7583-4bcd-a705-dae3eacdee85";
const tois_str = pipe(
  tois,
  arr_map((toi) => {
    return `## ${toi.year.toUpperCase()}
    
<img width="500" alt="${toi.year} logo" src="${toi.logo || NO_IMAGE}">

${toi.description ?? ""}

${toi.tasks
  .map(
    ([day, tasks]) => `### Day ${day > 0 ? day : "?"}
    
${tasks
  .map(
    (t) =>
      `- [${t.problem_id}](./${toi.year}/${t.problem_id}) ${
        t.problem_title
      }\n\n  <img width="350" alt="problem ${t.id}" src="${
        t.image || NO_IMAGE
      }">`
  )
  .join("\n\n")}
    `
  )
  .join("\n\n")}
    `;
  }),
  (arr) => arr.join("\n\n")
);

const root_readme = await async_pipe(
  fs.readFile(new URL("./README.md", root_dir), "utf-8"),
  (str) => codegen_replace_block(str, "@codegen_tois", tois_str),
  (str) => fs.writeFile(new URL("./README.md", root_dir), str)
);
// console.log(tois_str);
