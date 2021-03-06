// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chromeos/extensions/media_player_event_router.h"

#include "base/memory/singleton.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extension_system.h"

namespace extensions {

static void BroadcastEvent(Profile* profile, const std::string& event_name) {
  if (profile && extensions::ExtensionSystem::Get(profile)->event_router()) {
    scoped_ptr<base::ListValue> args(new base::ListValue());
    scoped_ptr<extensions::Event> event(new extensions::Event(
        event_name, args.Pass()));
    extensions::ExtensionSystem::Get(profile)->event_router()->
        BroadcastEvent(event.Pass());
  }
}

MediaPlayerEventRouter::MediaPlayerEventRouter(Profile* profile)
    : profile_(profile) {
}

MediaPlayerEventRouter::~MediaPlayerEventRouter() {
}

void MediaPlayerEventRouter::NotifyNextTrack() {
  BroadcastEvent(profile_, "mediaPlayerPrivate.onNextTrack");
}

void MediaPlayerEventRouter::NotifyPrevTrack() {
  BroadcastEvent(profile_, "mediaPlayerPrivate.onPrevTrack");
}

void MediaPlayerEventRouter::NotifyTogglePlayState() {
  BroadcastEvent(profile_, "mediaPlayerPrivate.onTogglePlayState");
}

}  // namespace extensions
