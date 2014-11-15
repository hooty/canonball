require 'spec_helper'

describe Canonball do
  it "verfiy delegation" do
    expect(Canonball).to respond_to :inialize_sdk,
                                    :terminate_sdk,
                                    :open_camera_session,
                                    :close_camera_session,
                                    :take_picture,
                                    :download_files
  end
end
