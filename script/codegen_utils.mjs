/**
 *
 * @param {string} str
 * @param {string} block_name
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
 * @param {string} block_name
 * @param {string} new_content
 */
export function codegen_replace_block(str, block_name, new_content) {
  const { idx_begin, idx_end } = codegen_find_block(str, block_name);
  return (
    str.slice(0, idx_begin) +
    "\n" +
    new_content.trim() +
    "\n" +
    str.slice(idx_end)
  );
}
