# Sidecar Subtitles Plugin for Brightcove Player SDK for iOS, version 1.0.1.41

Supported Platforms
===================

Supports iOS 7.0 and above.

Installation
============
You can use [Cocoapods][cocoapods] to add the Sidecar Subtitles Plugin for Brightcove Player SDK to your project. You can find the latest `Brightcove-Player-SDK-SidecarSubtitles` podspec [here][podspecs].

To add the Sidecar Subtitles Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
1. Download the latest zip'ed release of the plugin from our [release page][release].
1. Add the contents of Library and Headers to the project.
1. On the "Build Phases" tab of your application target, add the following to the "Link
    Binary With Libraries" phase:
    * `libBCOVSidecarSubtitles.a`
1. On the "Build Settings" tab of your application target:
    * Ensure that BCOVSidecarSubtitles headers are in your application's "Header Search Path".
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.

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

1. BCOVSidecarSubtitles adds some category methods to BCOVPlaybackManager. The first of these is `-createSidecarSubtitlesPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. Alternatively (if you are using more than one session provider), you can create a BCOVSSSessionProvider and pass that to the manager method that creates a playback controller with upstream session providers.\*

1. In order to retrieve web vtt files from your Brightcove account automatically, you need to use the `BCOVPlaybackService` instead of the BCOVCatalogService to retrieve your videos. If you need to use `BCOVCatalogService`, you will need to follow the directions in the "Manually populating subtitle data".

\* Note that `BCOVSSSessionProvider` should come before any session providers in the chain passed to the manager when constructing the playback controller. This plugin is **not compatible** with Widevine plugin.

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
           kBCOVSSTextTracksKeyDuration: ..., // required/optional
           kBCOVSSTextTracksKeyKind: kBCOVSSTextTracksKindSubtitles or kBCOVSSTextTracksKindCaptions, // required
           kBCOVSSTextTracksKeyDefault: ..., // optional
           kBCOVSSTextTracksKeyMIMEType: ..., // optional
       }
       @{...}, // second text track dictionary
       @{...}, // third text track dictionary
    ];
       
       BCOVVideo *video = [BCOVVideo alloc] initWithSource:<source> cuePoints:<cuepoints> properties:@{ kBCOVSSVideoPropertiesKeyTextTracks:subtitles }];

Known Issues
============

* This plugin currently does not support integrating with the Widevine Plugin for Brightcove Brightcove Player SDK for iOS.

* If your videos are being retrieved from the Brightcove Playback API, your renditions must include a master M3U8 playlist. The Sidecar Subtitle plugin does not work with single rendition M3U8 playlists.

* If you are providing a Subtitle playlist to the plugin, and that subtitle playlist includes links to web vtt files that respond as 404, playback will fail. This is a bug in Apple's AVPlayer.

