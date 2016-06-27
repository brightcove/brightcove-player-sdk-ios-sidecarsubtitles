# Sidecar Subtitles Plugin for Brightcove Player SDK for iOS and tvOS, version 2.1.0.95

Supported Platforms
===================

iOS 7.0 and above.

tvOS 9.0 and above.

Installation
============
The Sidecar Subtitles plugin for the Brightcove Player SDK provides two installation packages for iOS, a static library framework and a dynamic framework. The static library target supports deployment on iOS 7 while the dynamic framework only supports iOS 8 and above. For tvOS, The Sidecar Subtitles plugin provides a dynamic framework only.

CocoaPods
--------------

You can use [CocoaPods][cocoapods] to add the Sidecar Subtitles Plugin for Brightcove Player SDK to your project. You can find the latest `Brightcove-Player-SDK-SidecarSubtitles` podspec [here][podspecs].

Specifying the default pod `Brightcove-Player-SDK-SidecarSubtitles` will install the static library framework. To install the dynamic framework, declare the pod with the `dynamic` subspec: `Brightcove-Player-SDK-SidecarSubtitles/dynamic`

Static Framework example:

    pod 'Brightcove-Player-SDK-SidecarSubtitles'
    
Dynamic Framework example:

    pod 'Brightcove-Player-SDK-SidecarSubtitles/dynamic'    
    
Manual
--------------

To add the Sidecar Subtitles Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zipped release of the BrightcoveSidecarSubtitles plugin from our [release page][release].
3. Add `BrightcoveSidecarSubtitles.framework` to your project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. (Dynamic Framework only) On the "General" tab of your application target, add 'BrightcoveSidecarSubtitles.framework' to the "Embedded Binaries" section.
6. (Dynamic Framework only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveSidecarSubtitles.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission. ([rdar://19209161][19209161])
7. (Static Framework only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.

Imports
--------------
The Brightcove Player SDK for iOS can be imported into code a few different ways:

* `@import BrightcoveSidecarSubtitles;`
* `#import <BrightcoveSidecarSubtitles/BrightcoveSidecarSubtitles.h>`
* `#import <BrightcoveSidecarSubtitles/[specific class].h>`.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/CocoaPods/Specs/tree/master/Specs/Brightcove-Player-SDK-SidecarSubtitles
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-sidecarsubtitles/releases
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
Quick Start
===========


        NSString *policyKey;  // (Brightcove Playback API policy Key)
        NSString *videoID; // (ID of the video you wish to use)
        NSString *accountId;  // account id

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    [1] id<BCOVPlaybackController> controller = [playbackManager createSidecarSubtitlesPlaybackControllerWithViewStrategy:[manager defaultControlsViewStrategy]];
        [self.view addSubview:controller.view];

        BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:accoundId policyKey:policyKey];
    [2] [playbackService findVideoWithVideoID:videoID
                                 parameters:nil
                                 completion:^(BCOVVideo *video,
                                              NSDictionary *jsonResponse,
                                              NSError      *error) {

                                     [controller setVideos:@[ video ]];
                                     [controller play];

                                 }];


Let's break this code down into steps, to make it a bit simpler to digest:

1. BCOVSidecarSubtitles adds some category methods to BCOVPlaybackManager. The first of these is `-createSidecarSubtitlesPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. Alternatively (if you are using more than one session provider), you can create a BCOVSSSessionProvider and pass that to the manager method that creates a playback controller with upstream session providers.\* If you are developing for tvOS, the ViewStrategy passed to createSidecarSubtitlesPlaybackControllerWithViewStrategy will be nil.

1. In order to retrieve web vtt files from your Brightcove account automatically, you need to use the `BCOVPlaybackService` instead of the BCOVCatalogService to retrieve your videos. If you need to use `BCOVCatalogService`, you will need to follow the directions in the "Manually populating subtitle data".

\* Note that `BCOVSSSessionProvider` should come before any session providers in the chain passed to the manager when constructing the playback controller. This plugin is **not compatible** with the Widevine plugin.

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at https://groups.google.com/forum/#!forum/brightcove-native-player-sdks .

Manually populating subtitle data
=================================
The BCOVSidecarSubtitle plugin will look for the presence of an array of subtitle metadata in the `BCOVVideo` object properties, keyed by kBCOVSSVideoPropertiesKeyTextTracks. If you are using `BCOVPlaybackService` to retrieve videos and those videos have text tracks associated with them, this will be populated automatically.

If you are a providing your own videos, are a Perform customer or trying to use `BCOVCatalogService`, you will need to structure the data as shown below:

     NSArray *subtitles = @[
        @{
           kBCOVSSTextTracksKeySource: ..., // required
           kBCOVSSTextTracksKeySourceLanguage: ..., // required
           kBCOVSSTextTracksKeyLabel: ..., // required
           kBCOVSSTextTracksKeyDuration: ..., // required/optional [1]
           kBCOVSSTextTracksKeyKind: kBCOVSSTextTracksKindSubtitles or kBCOVSSTextTracksKindCaptions, // required
           kBCOVSSTextTracksKeyDefault: ..., // optional
           kBCOVSSTextTracksKeyMIMEType: ..., // optional
       }
       @{...}, // second text track dictionary
       @{...}, // third text track dictionary
    ];
       
       BCOVVideo *video = [BCOVVideo alloc] initWithSource:<source> cuePoints:<cuepoints> properties:@{ kBCOVSSVideoPropertiesKeyTextTracks:subtitles }];

Notes
============
1. kBCOVSSTextTracksKeyDuration is a required key if you are using caption files with a .vtt extension. kBCOVSSTextTracksKeyDuration is an optional key if you are using using caption files with a .m3u8 extension.

Please refer to the code documentation in the BCOVSSComponent.h header file for more information on usage of these keys.

Known Issues
============

* This plugin currently does not support integrating with the Widevine Plugin for Brightcove Brightcove Player SDK for iOS.

* If your videos are being retrieved from the Brightcove Playback API, your renditions must include a master M3U8 playlist. The Sidecar Subtitle plugin does not work with single rendition M3U8 playlists.

* If you are providing a Subtitle playlist to the plugin, and that subtitle playlist includes links to web vtt files that respond as 404, playback will fail. This is a bug in Apple's AVPlayer.
