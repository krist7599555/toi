import * as fs from "node:fs";
import * as path from "node:path";
import { pipe } from "@krist7599555/lodosh";
import { arr_map } from "@krist7599555/lodosh";
import { glob } from "glob";
import { async_pipe } from "ts-async-pipe";
import { group_by } from "@krist7599555/lodosh";
import { group_by_with } from "@krist7599555/lodosh";
import { group } from "node:console";
import { find_match } from "@krist7599555/lodosh";
import { arr_filter } from "@krist7599555/lodosh";
import { is_match } from "@krist7599555/lodosh";
import { arr_filter_map } from "@krist7599555/lodosh";
const root_dir = new URL("../", import.meta.url);

const dir = await async_pipe(
  glob("./toi*/toi*/*.{cpp,md,pdf}", {
    cwd: root_dir,
  }),
  arr_map((filename) => {
    return {
      ext: path.extname(filename),
      basename: path.basename(filename),
      year: path.dirname(path.dirname(filename)),
      task: path.basename(path.dirname(filename)),
      fullpath: new URL(filename, root_dir),
    };
  }),
  group_by_with(
    (it) => it.task,
    (arr) => {
      return {
        year: arr[0].year,
        task: arr[0].task,
        pdf: find_match(arr, { ext: ".pdf" })?.basename,
        md: pipe(
          find_match(arr, { basename: "README.md" }).fullpath,
          (path) => fs.readFileSync(path, "utf-8"),
          (md) => {
            const regex_exec = /<img.*?src=\"(.*)\"/gm.exec(md);
            // if (!problem_image) {
            //   console.warn("no image", md);
            // }
            return {
              problem_image: regex_exec?.[1] ?? null,
              editorial: regex_exec
                ? md
                    .slice(regex_exec.index)
                    .split("\n")
                    .slice(1)
                    .join("\n")
                    .trim()
                : null,
            };
          }
        ),
        cpp: arr_filter_map(arr, (it) =>
          is_match(it, { ext: ".cpp" }) ? it.basename : null
        ),
      };
    }
  )
);
console.log(JSON.stringify(dir, null, 2));
