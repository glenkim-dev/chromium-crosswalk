// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chromeos/chromeos_switches.h"

namespace chromeos {
namespace switches {

// Path for app's OEM manifest file.
const char kAppOemManifestFile[]            = "app-mode-oem-manifest";

// When wallpaper boot animation is not disabled this switch
// is used to override OOBE/sign in WebUI init type.
// Possible values: parallel|postpone. Default: parallel.
const char kAshWebUIInit[]                  = "ash-webui-init";

// Enables overriding the path for the default authentication extension.
const char kAuthExtensionPath[]             = "auth-ext-path";

// Forces the stub implementation of dbus clients.
const char kDbusStub[] = "dbus-stub";

// All stub networks are idle by default.
const char kDefaultStubNetworkStateIdle[] = "default-stub-network-state-idle";

// Time before a machine at OOBE is considered derelict
const char kDerelictDetectionTimeout[] = "derelict-detection-timeout";

// Time before a derelict machines starts demo mode.
const char kDerelictIdleTimeout[] = "derelict-idle-timeout";

// Disables wallpaper boot animation (except of OOBE case).
const char kDisableBootAnimation[]          = "disable-boot-animation";

// Disables Google Drive integration.
const char kDisableDrive[]                  = "disable-drive";

// Disables the ChromeOS demo.
const char kDisableDemoMode[]               = "disable-demo-mode";

// Disables reporting recently logged in users for enterprise-managed devices.
const char kDisableEnterpriseUserReporting[] =
    "disable-enterprise-user-reporting";

// Disable Genius App and use the original Help App instead.
const char kDisableGeniusApp[]              = "disable-genius-app";

// Disable to show the indicator about the IME (input method editor) mode
// on Chrome OS.
const char kDisableIMEModeIndicator[] = "disable-ime-mode-indicator";

// Disable policy-configured local accounts.
const char kDisableLocalAccounts[]          = "disable-local-accounts";

// Avoid doing expensive animations upon login.
const char kDisableLoginAnimations[]        = "disable-login-animations";

// Disable new channel switcher UI.
const char kDisableNewChannelSwitcherUI[]   = "disable-new-channel-switcher-ui";

// Disables new Kiosk UI when kiosk apps are represented as user pods.
const char kDisableNewKioskUI[]             = "disable-new-kiosk-ui";

// Disable Quickoffice component app thus handlers won't be registered so
// it will be possible to install another version as normal app for testing.
const char kDisableQuickofficeComponentApp[] =
    "disable-quickoffice-component-app";

// Disables volume adjust sound.
const char kDisableVolumeAdjustSound[] = "disable-volume-adjust-sound";

// Disables fetching online CrOS EULA page, only static version is shown.
const char kDisableOnlineEULA[] = "disable-cros-online-eula";

// Avoid doing animations upon oobe.
const char kDisableOobeAnimation[]          = "disable-oobe-animation";

// Disables portal detection and network error handling before auto
// update.
const char kDisableOOBEBlockingUpdate[] =
    "disable-oobe-blocking-update";

// Enables overriding the path for the default echo component extension.
// Useful for testing.
const char kEchoExtensionPath[]             = "echo-ext-path";

// Enables component extension that initializes background pages of
// certain hosted applications.
const char kEnableBackgroundLoader[]        = "enable-background-loader";

// Enables switching between different cellular carriers from the UI.
const char kEnableCarrierSwitching[]        = "enable-carrier-switching";

// Enable "interactive" mode for stub implemenations (e.g. NetworkStateHandler)
const char kEnableStubInteractive[] = "enable-stub-interactive";

// Enable stub portalled wifi network for testing.
const char kEnableStubPortalledWifi[] = "enable-stub-portalled-wifi";

// Enables touchpad three-finger-click as middle button.
const char kEnableTouchpadThreeFingerClick[]
    = "enable-touchpad-three-finger-click";

// Specifies stub network types to be enabled.  If this switch is not specified,
// ethernet, wifi and vpn are enabled by default.
//
// Examples:
// Disable all network types: --enabled-stub-network-types=''
// Enable wifi only: --enabled-stub-network-types=wifi
// Enable ethernet and wifi: --enabled-stub-network-types=ethernet,wifi
const char kEnabledStubNetworkTypes[] = "enabled-stub-network-types";

// Enable Kiosk mode for ChromeOS. Note this switch refers to retail mode rather
// than the kiosk app mode.
const char kEnableKioskMode[]               = "enable-kiosk-mode";

// Enables request of tablet site (via user agent override).
const char kEnableRequestTabletSite[]       = "enable-request-tablet-site";

// Power of the power-of-2 initial modulus that will be used by the
// auto-enrollment client. E.g. "4" means the modulus will be 2^4 = 16.
const char kEnterpriseEnrollmentInitialModulus[] =
    "enterprise-enrollment-initial-modulus";

// Power of the power-of-2 maximum modulus that will be used by the
// auto-enrollment client.
const char kEnterpriseEnrollmentModulusLimit[] =
    "enterprise-enrollment-modulus-limit";

// Don't create robot account on enrollment. Used when testing device
// enrollment against YAPS or the Python test server.
const char kEnterpriseEnrollmentSkipRobotAuth[] =
    "enterprise-enrollment-skip-robot-auth";

// Shows the selecting checkboxes in the Files.app.
const char kFileManagerShowCheckboxes[]     = "file-manager-show-checkboxes";

// Enables the new audio player in the Files.app.
const char kFileManagerEnableNewAudioPlayer[] =
    "file-manager-enable-new-audio-player";

// Enables the multi-profile support in the Files.app.
const char kFileManagerEnableMultiProfile[] =
    "file-manager-enable-multi-profile";

// Passed to Chrome the first time that it's run after the system boots.
// Not passed on restart after sign out.
const char kFirstExecAfterBoot[]            = "first-exec-after-boot";

// Usually in browser tests the usual login manager bringup is skipped so that
// tests can change how it's brought up. This flag disables that.
const char kForceLoginManagerInTests[]      = "force-login-manager-in-tests";

// Makes GPU sandbox failures nonfatal.
const char kGpuSandboxFailuresNonfatal[] = "gpu-sandbox-failures-nonfatal";

// Indicates that the browser is in "browse without sign-in" (Guest session)
// mode. Should completely disable extensions, sync and bookmarks.
const char kGuestSession[]                  = "bwsi";

// If true, the Chromebook has a Chrome OS keyboard. Don't use the flag for
// Chromeboxes.
const char kHasChromeOSKeyboard[]           = "has-chromeos-keyboard";

// If true, the Chromebook has a keyboard with a diamond key.
const char kHasChromeOSDiamondKey[]         = "has-chromeos-diamond-key";

// Path for the screensaver used in Kiosk mode
const char kKioskModeScreensaverPath[]      = "kiosk-mode-screensaver-path";

// Allows override of oobe for testing - goes directly to the login screen.
const char kLoginScreen[]                   = "login-screen";

// Enables Chrome-as-a-login-manager behavior.
const char kLoginManager[]                  = "login-manager";

// Specifies a password to be used to login (along with login-user).
const char kLoginPassword[]                 = "login-password";

// Specifies the profile to use once a chromeos user is logged in.
const char kLoginProfile[]                  = "login-profile";

// Specifies the user which is already logged in.
const char kLoginUser[]                     = "login-user";

// Enables natural scroll by default.
const char kNaturalScrollDefault[]          = "enable-natural-scroll-default";

// Skips all other OOBE pages after user login.
const char kOobeSkipPostLogin[]             = "oobe-skip-postlogin";

// Interval at which we check for total time on OOBE.
const char kOobeTimerInterval[]             = "oobe-timer-interval";

// Integer flag that sets the DeviceRegistered local state pref.
const char kDeviceRegistered[]              = "device-registered";

// Skips the machine hwid check. Useful for running in VMs because they have no
// hwid.
const char kSkipHWIDCheck[]                 = "skip-hwid-check";

// Sends test messages on first call to RequestUpdate (stub only).
const char kSmsTestMessages[]               = "sms-test-messages";

// Indicates that a stub implementation of CrosSettings that stores settings in
// memory without signing should be used, treating current user as the owner.
// This option is for testing the chromeos build of chrome on the desktop only.
const char kStubCrosSettings[]              = "stub-cros-settings";

// Disables user image sync.
const char kDisableUserImageSync[]          = "disable-user-image-sync";

// Disables SAML sigin support.
const char kDisableSamlSignin[]             = "disable-saml-signin";

// Overrides the manifest of the GAIA auth extension with the given file.
const char kGAIAAuthExtensionManifest[]     = "gaia-auth-extension-manifest";

// Disables new first-run overlay UI.
const char kDisableFirstRunUI[] = "disable-first-run-ui";

// Enables animated transitions during first-run tutorial.
const char kEnableFirstRunUITransitions[] = "enable-first-run-ui-transitions";

// Forces first-run UI to be shown for every login.
const char kForceFirstRunUI[] = "force-first-run-ui";

// Enables testing for auto update UI.
const char kTestAutoUpdateUI[] = "test-auto-update-ui";

// Enables features required for supervised user sync,
const char kEnableSupervisedPasswordSync[] = "enable-supervised-password-sync";

}  // namespace switches
}  // namespace chromeos
