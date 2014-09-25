# Canonball

[ ![Codeship Status for hooty/canonball](https://www.codeship.io/projects/9a884970-26f6-0132-7b27-1a72e97eb705/status)](https://www.codeship.io/projects/37606)
[![Code Climate](https://codeclimate.com/github/hooty/canonball/badges/gpa.svg)](https://codeclimate.com/github/hooty/canonball)
[![Test Coverage](https://codeclimate.com/github/hooty/canonball/badges/coverage.svg)](https://codeclimate.com/github/hooty/canonball)


Magic sauce ruby wrapper for canon EOS EDSDK. This is a wrapper for a C library that take photos and download and delete them from the camera.

## Installation

Add this line to your application's Gemfile:

    gem 'canonball'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install canonball

## Applying for SDK access
Before you can use this library you need to obtain the EDSDK native library from Canon. You can do so via their developers program: 

- [Canon Europe](http://www.didp.canon-europa.com/)
- [Canon USA](http://www.usa.canon.com/cusa/consumer/standard_display/sdk_homepage)
- [Canon Asia](http://www.canon-asia.com/personal/web/developerresource)
- [Canon Oceania](https://www.canon.co.nz/en-NZ/Personal/Support-Help/Support-News/Canon-SDK)

Once you were granted access - this may take a few days - download the latest version of their library and follow the usage instructions.

This currently only works with OSX. You will need drop "EDSDK.framework" into "/System/Library/Frameworks/".

## Usage

Take a photo:

    camera_index = 0
    Canonball.take_picture(camera_index)

Download photo(s):

    camera_index = 0
    Canonball.download_files(camera_index,"./photo_folder/")

## Contributing

1. Fork it ( http://github.com<my-github-username>/canonball/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
