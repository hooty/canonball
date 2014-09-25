require 'spec_helper'

describe Canonball do
  it "verfiy delegation" do
    expect(Canonball).to respond_to :take_picture, :download_files
  end
end
