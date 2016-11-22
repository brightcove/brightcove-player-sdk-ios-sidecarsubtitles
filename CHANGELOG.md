# 2.1.2
### Additions and Improvements
* The podspec now supports version 5.2 of the Brightcove Player SDK for iOS.
* The minimum supported deployment target is now iOS 8.0.

# 2.1.1
### Additions and Improvements
* Fixes an issue where some advanced HLS streams would become unplayable when sidecar subtitles were added to them (specifically, streams whose manifest contained EXT-X-MEDIA tags without an embedded URI).
* Fixes an issue where some HLS manifests that used relative URLs with query strings would become unplayable when sidecar subtitles were added to them.

# 2.1.0
### Breaking Changes
* You must use the Brightcove Player SDK for iOS version 5.1.0+.

# 2.0.3
### Additions and Improvements
* Fixes a playback problem that occurred when using Sidecar Subtitles in combination with videos that are sourced outside of the Brightcove Videocloud, and have extra query/fragment information in the URL.

# 2.0.2
### Additions and Improvements
* Adds dynamic framework support for tvOS.

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