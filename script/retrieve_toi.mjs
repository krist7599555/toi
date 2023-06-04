import {
  arr_filter,
  arr_filter_map,
  arr_map,
  group_by,
  is_match,
  pipe,
  record_values,
  sort_by,
} from "@krist7599555/lodosh";
import * as csv from "csv/sync";
import { glob } from "glob";
import * as fs from "node:fs/promises";
import * as path from "node:path";
import { async_pipe } from "ts-async-pipe";
import * as yaml from "yaml";
import { codegen_replace_block_string } from "./codegen_utils.mjs";

const root_dir = new URL("../", import.meta.url);

/**
 * retrieve data from
 * - [meta_toi_problems.csv](../meta_toi_problems.csv)
 */
export async function retrieve_meta_toi_problems() {
  return await async_pipe(
    fs.readFile(new URL("./meta_toi_problems.csv", root_dir)),
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
}

/**
 * retrieve data from
 * - [meta_toi_competitions.yaml](../meta_toi_competitions.yaml)
 */
export async function retrieve_meta_toi_competitions() {
  const problems = await retrieve_meta_toi_problems();
  const tois = await async_pipe(
    fs.readFile(new URL("./meta_toi_competitions.yaml", root_dir), "utf-8"),
    (buf) => yaml.parse(buf),
    record_values,
    sort_by((it) => [["desc", it.order]]),
    arr_map((it) => {
      const year = `toi${it.order}`;
      return {
        /** @type {`toi${number}`} */
        year,
        logo: `${it.logo || ""}` || null,
        order: +it.order,
        description: `${it.description || ""}` || null,
        tasks: pipe(
          problems,
          arr_filter(is_match({ year })),
          group_by((it) => it.day)
        ),
      };
    })
  );

  return tois;
}
