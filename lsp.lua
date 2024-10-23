-- Import the lspconfig plugin
local lspconfig = require('lspconfig')

-- Define common capabilities if you are using a plugin like nvim-cmp (optional)
local capabilities = vim.lsp.protocol.make_client_capabilities()
-- Example: Extend capabilities with nvim-cmp (optional)
-- capabilities = require('cmp_nvim_lsp').default_capabilities(capabilities)

-- Function to attach key mappings and custom LSP behavior for each server
local on_attach = function(client, bufnr)
  local opts = { noremap = true, silent = true }

  -- Key mappings based on LSP capabilities
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'gd', '<Cmd>lua vim.lsp.buf.definition()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'GD', '<Cmd>lua vim.lsp.buf.declaration()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'gy', '<Cmd>lua vim.lsp.buf.type_definition()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'gi', '<Cmd>lua vim.lsp.buf.implementation()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', '<C-k>', '<Cmd>lua vim.lsp.buf.signature_help()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'K', '<Cmd>lua vim.lsp.buf.hover()<CR>', opts)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', '<leader>rn', '<Cmd>lua vim.lsp.buf.rename()<CR>', opts)

  -- Highlight symbol under cursor if supported by the server
  if client.server_capabilities.documentHighlightProvider then
    vim.cmd [[
      autocmd CursorHold <buffer> lua vim.lsp.buf.document_highlight()
      autocmd CursorMoved <buffer> lua vim.lsp.buf.clear_references()
    ]]
  end

  -- Enable automatic formatting on save if the server supports it
  if client.server_capabilities.documentFormattingProvider then
    vim.cmd [[
      autocmd BufWritePre <buffer> lua vim.lsp.buf.format()
    ]]
  end
end

-- Enable clangd server with a specific command
lspconfig.clangd.setup {
  cmd = { '/home/1337encrypted/esp/esp-clang/bin/clangd' }, -- Adjust this path as needed
  capabilities = capabilities,
  on_attach = on_attach,
}
