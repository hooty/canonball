# coding: UTF-8
require 'ffi'
require "canonball/version"
require "canonball/error_codes"

module Canonball
  extend FFI::Library
  ffi_lib "#{File.expand_path(File.dirname(__FILE__))}/canonball/canonball.so"
  attach_function :inialize_sdk, [], :int
  attach_function :terminate_sdk, [], :int
  attach_function :open_camera_session, [ :int ], :int
  attach_function :close_camera_session, [], :int
  attach_function :take_picture, [], :int
  attach_function :press_shutter_button, [], :int
  attach_function :press_shutter_button_non_af, [], :int
  attach_function :download_files, [ :int, :string], :int
end