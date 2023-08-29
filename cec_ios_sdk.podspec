#
# Be sure to run `pod lib lint cec_ios_sdk.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'cec_ios_sdk'
  s.version          = '0.1.1'
  s.summary          = 'Customer Engagement Cloud SDK'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
  Customer Engagement Cloud SDK by easemob, this is not a offical pod.
                       DESC

  s.homepage         = 'https://github.com/dash-chan/cec_ios_sdk'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'laiiihz' => '' }
  s.source           = { :git => 'https://github.com/dash-chan/cec_ios_sdk.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.platform         = :ios, '11.0'
  s.vendored_frameworks = 'sdk/HelpDesk.xcframework', 'sdk/HyphenateChat.xcframework'
  s.pod_target_xcconfig = { 'VALID_ARCHS' => 'armv7 x86_64 arm64' }
end
