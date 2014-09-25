require 'ffi'
require "canonball/version"

module Canonball
  extend FFI::Library
  ffi_lib "./lib/canonball/canonball.so"
  attach_function :take_picture, [ :int ], :int
  attach_function :download_files, [ :int, :string], :int
end