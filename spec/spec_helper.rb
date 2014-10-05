require "codeclimate-test-reporter"
CodeClimate::TestReporter.start
require "canonball"

RSpec.configure do |config|
  config.order = "random"
  Kernel.srand config.seed
  config.mock_with :rspec do |mocks|
    mocks.verify_doubled_constant_names = true
  end
end

