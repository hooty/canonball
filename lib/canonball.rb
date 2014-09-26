# coding: UTF-8
require 'ffi'
require "canonball/version"

module Canonball
  extend FFI::Library
  ffi_lib "#{File.expand_path(File.dirname(__FILE__))}/canonball/canonball.so".force_encoding("utf-8")
  attach_function :take_picture, [ :int ], :int
  attach_function :download_files, [ :int, :string], :int
end