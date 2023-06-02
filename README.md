# chs-element-desktop

## Description

This repository builds a mirror of [Element Desktop](https://github.com/vector-im/element-desktop) with default homeserver different from [matrix.org](https://matrix.org).

The Element mirror created with this repository supports autoupdating on MacOS and Windows (as usual Element do). It can be installed on the same device with usual Element.

Builds are signed only on MacOS.

## Configure

To build your version of Element with this repository, you should

1. Own a storage on [Exoscale](https://www.exoscale.com/) (you can switch to other s3-compatible storages)
2. Own an account on [Apple Developer](https://developer.apple.com/)
3. Copy this repository and set 14 secrets as described below
4. Run one github action (descibed below)

### Secrets, part 1 (defaults).
1. `USER_HOMESERVER` - the server you want users to connect to. Example: `matrix.org`.

2. `USER_UPDATE_FOLDER` - the folder on your storage you want to store updates in. You don't need to create this folder manually - it will be created automatically. Example: `https://packages.element.io/desktop/update/`.

Both these secrets will be visible to users.

### Secrets, part 2 (storage).

3. `API` - the root of your storage. Example: `sos-de-fra-1.exo.io`.
4. `API_BUCKET_NAME` - path from the root of your storage to the folder with updates. It should hold that `https://API/API_BUCKET_NAME/update/ = USER_UPDATE_FOLDER`.
5. `API_ACCESS_KEY`
6. `API_SECRET_KEY`

These are access and secret key for account with write access on your storage.

### Secrets, part 3 (naming).
7. `NAMING_APP_NAME_SUFFIX`.
8. `NAMING_APP_DATA_NAME_SUFFIX`.

These are used in naming part. `NAMING_APP_NAME_SUFFIX` is user-visible, `NAMING_APP_DATA_NAME_SUFFIX` is more system-related. Your version of Element will be called `Element${NAMING_APP_NAME_SUFFIX}`.

Note that `NAMING_APP_NAME_SUFFIX` should begin with space if you want to add space after `Element` in the title.

Do not leave any of these empty if you expect user using both usual Element and your version of Element. Do not use other characters than latin letters, digits, spaces, dashes, brackets and interpuncts in `NAMING_APP_NAME_SUFFIX`. Do not use other characters than latin letters, digits and dashes in `NAMING_APP_DATA_NAME_SUFFIX`.

### Secrets, part 4 (macOS signing).

Signing is required for autoupdates on macOS. Also it makes it easier to enter the app for the first time on macOS. Windows and Linux are less sensitive to signing.

9. `APPLE_CSC_LINK` - your Developer ID Certificate in base64 format.
10. `APPLE_CSC_KEY_PASSWORD` - password from your certificate.
11. `APPLE_ID` - your Apple ID.
12. `APPLE_ID_PASSWORD` - your App Specific Password for App Store Connect.
13. `APPLE_TEAM_ID` - your Developer Team ID.
14. `NAMING_APP_ID` - CFBundleIdentifier of your app.

These all are required to sign your app.
`APPLE_ID` and `APPLE_ID_PASSWORD` are obvious ones. You can find `APPLE_TEAM_ID` in your Developer account.

[Open this link](https://developer.apple.com/account/resources/identifiers/list) to register `NAMING_APP_ID`. Click on plus near `Identifiers` and follow instructions after it. `NAMING_APP_ID` is used for builds on other platforms, too.

To create and export Developer ID Certificate follow these instructions on Mac:
- First, create certificate according to [this instruction](https://developer.apple.com/help/account/create-certificates/create-developer-id-certificates). Do not forget to install the certificate in your keychain by double-clicking on it.
- Then export your certificate to `.p12` format as in [this instruction](https://ioscodesigning.com/exporting-code-signing-files/#exporting-manually). Set secure password in the step 5.

You can use your Developer ID Certificate for multiple apps so you don't have to create a new one if you already have it.

Set secret `APPLE_CSC_LINK` as the result of running command `base64 -i PathToYourCertificate`, where `PathToYourCertificate` is path to your Developer ID Certificate in `.p12` format. Set secret `APPLE_CSC_KEY_PASSWORD` as the password you set in the step 5 of the second of instructions above.

[More detailed signing instruction in Russian.](https://docs.google.com/document/d/1eHp5cwMbsJO5Hs500iqqBsoovCRjJYtElzw0MAGHKjQ/edit?usp=sharing)

## Build

After correctly setting 14 secrets as described above in your copy of this repository go to GitHub Actions page of your repository.

Run action `Check New Version` with option `Build the latest version anyway` on. It will build the latest version of Element Desktop with your homeserver. Installers will be added to Github Releases in your repository and to your storage.

Each day at 2:00 UTC your repository will check if new version of Element is available and will build it if required.

If you want to generate download links, run action `Generate Links` with version of Element you just build. These links would be added to the corresponding Release.
