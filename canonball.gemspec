# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'canonball/version'

Gem::Specification.new do |spec|
  spec.name          = "canonball"
  spec.version       = Canonball::VERSION
  spec.authors       = ["Jon Christopher"]
  spec.email         = ["joncirca@icloud.com"]
  spec.summary       = %q{canon camera sdk.}
  spec.description   = %q{Magic sauce ruby wrapper for canon EOS EDSDK.}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency 'bundler', '~> 1.5'
  spec.add_development_dependency 'rake', '~> 10.3.2'
  spec.add_development_dependency 'rspec', '~> 3.1.0'

  spec.add_dependency 'ffi', '~> 1.9.4'

end