puts Canonball.inialize_sdk
puts Canonball.open_camera_session 0
t = Time.now
puts Canonball.take_picture 0
puts Time.now - t
puts Canonball.download_files 0, "#{File.expand_path(File.dirname(__FILE__))}/download/"
puts Canonball.close_camera_session 0
puts Canonball.terminate_sdk
