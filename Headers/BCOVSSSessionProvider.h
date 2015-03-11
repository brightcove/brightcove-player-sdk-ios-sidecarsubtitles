//
// BCOVSSSessionProvider.h
// BCOVSS
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import "BCOVPlayerSDK.h"

@import Foundation;

@class BCOVSSSessionProviderOption;


/**
 * Session provider implementation that delivers playback sessions with support
 * for subtitles.
 *
 * Instances of this class should not be created directly by clients of the
 * Brightcove Player SDK for iOS; instead use the `-[BCOVPlayerSDKManager createSidecarSubtitlesSessionProviderWithOptions:]`
 * factory method (which is added as a category method).
 */
@interface BCOVSSSessionProvider : NSObject <BCOVPlaybackSessionProvider>

@end


/**
 * Optional configuration for sidecar subtitles session providers.
 */
@interface BCOVSSSessionProviderOption : NSObject

@end


@interface BCOVSSSessionProvider (Unavailable)

- (instancetype)init __attribute__((unavailable("Use `-[BCOVPlayerSDKManager createSidecarSubtitlesSessionProviderWithOptions:]` instead.")));

@end