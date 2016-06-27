# 2.1.0
### Breaking Changes
* You must use the Brightcove Player SDK for iOS version 5.1.0+.

# 2.0.3
### Additions and Improvements
* Fixed a playback problem that occurred when using Sidecar Subtitles in combination with videos that are sourced outside of the Brightcove Videocloud, and have extra query/fragment information in the URL.

# 2.0.2
### Additions and Improvements
* Added dynamic framework support for tvOS.

# 2.0.1
### Additions and Improvements
* Reformatted the framework's short version string to comply with App Store submission requirements.


# 2.0.0
### Breaking Changes
* The static library distributable has been removed. If installed manually (not CocoaPods), you will need to remove `libBCOVSidecarSubtitles.a` and its headers from the Header Search Path. Please see README.md for new install options (including a static library framework).
* Header `BCOVSidecarSubtitles.h` has been removed. Please see README.md for new import options.


### Additions and Improvements
* Bitcode support.
* Support for more types of HLS manifests.
* You must use the Brightcove Player SDK for iOS version 5.0.1+.

# 1.0.1
### Additions and Improvements
* Internal Improvements.
* You must use the Brightcove Player SDK for iOS version 4.4.0+.
#