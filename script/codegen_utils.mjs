/**
 *
 * @param {string} str
 * @param {`@codegen_${string}`} block_name
 */
export function codegen_find_block(str, block_name) {
  const tag_begin = `<!-- ${block_name} begin -->`;
  const tag_end = `<!-- ${block_name} end -->`;
  const idx_begin = str.indexOf(tag_begin);
  const idx_end = str.indexOf(tag_end);
  console.log({ block_name, idx_begin, idx_end });
  if (idx_begin == -1) throw new Error(`not found ${tag_begin}`);
  if (idx_end == -1) throw new Error(`not found ${tag_end}`);
  if (idx_begin > idx_end)
    throw new Error(`${tag_begin} show before ${tag_end}`);
  return {
    idx_begin: idx_begin + tag_begin.length,
    idx_end,
    content: str
      .slice(str.indexOf(tag_begin) + tag_begin.length, idx_end)
      .trim(),
  };
}

/**
 *
 * @param {string} str
 * @param {`@codegen_${string}`} block_name
 * @param {string} new_content
 */
export function codegen_replace_block_string(str, block_name, new_content) {
  const { idx_begin, idx_end } = codegen_find_block(str, block_name);
  return (
    str.slice(0, idx_begin) +
    "\n" +
    new_content.trim() +
    "\n" +
    str.slice(idx_end)
  );
}

/**
 * Replace @codegen block of .file
 * @param {{file: URL, codegen_block: `@codegen_${string}`, replacer: (old_content: string) => string | Promise<string> }} opt
 */
export async function codegen_override_block(opt) {
  const fs = await import("node:fs/promises");
  const old_content = await fs.readFile(opt.file, "utf-8");
  const new_content = codegen_replace_block_string(
    old_content,
    opt.codegen_block,
    await opt.replacer(old_content)
  );
  await fs.writeFile(opt.file, new_content);
}

/**
 *
 * @param {string} str
 * @param {(str: string) => boolean} pred_string
 * @param {[string, ...string[]]} lines
 * @returns
 */
export function string_insertline_after(str, pred_string, added_lines) {
  const lines = str.split("\n");
  const head_idx = lines.findIndex((it) => pred_string(it));
  if (head_idx != -1) {
    lines.splice(head_idx + 1, 0, ...added_lines);
  }
  return lines.join("\n");
}
