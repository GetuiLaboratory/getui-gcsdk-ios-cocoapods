#
#  Be sure to run `pod spec lint GCSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|
  # 名称，pod search 搜索的关键词,注意这里一定要和.podspec的名称一样,否则报错
  s.name         = "GCSDK"
  # 版本号/库原代码的版本
  s.version      = "2.1.0.1"
  # 简介
  s.summary      = "个数 iOS SDK CocoaPods 集成库"
  # 项目主页地址
  s.homepage     = "https://github.com/GetuiLaboratory/getui-gcsdk-ios-cocoapods"
  # 许可证/所采用的授权版本
  s.license      = "MIT"
  # 库的作者
  s.author       = { "个推" => "support@getui.com" }
  # 项目的地址
  s.source       = { :git => "https://github.com/GetuiLaboratory/getui-gcsdk-ios-cocoapods.git", :tag => "#{s.version}" }
  # 支持的平台及版本
  s.platform     = :ios

  s.platform     = :ios, "7.0"
  # iOS支持的pod最低版本 / iOS对应的版本
  s.ios.deployment_target = "7.0"
  # 需要包含的源文件
  s.source_files  = 'GTCountSDK.h'
  # 使用了第三方静态库
  s.ios.vendored_libraries = 'libGTCommonSDK.a', 'libGTCountSDK.a'
  # s.ios.vendored_frameworks = 'GeYanSdk.framework'
  # 所需的framework，多个用逗号隔开
  s.frameworks = 'AdSupport'
  # “弱引用”所需的framework，多个用逗号隔开
  # s.ios.weak_frameworks = 'WebKit'
  # 所需的library，多个用逗号隔开
  s.libraries = "sqlite3.0","z"
  # 是否使用ARC，如果指定具体文件，则具体的问题使用ARC
  s.requires_arc = true

end
