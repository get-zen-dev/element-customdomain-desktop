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
7. `NAMING_APP_NAME_SUFFIX`
8. `NAMING_APP_DATA_NAME_SUFFIX`

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

`APPLE_ID` and `APPLE_ID_PASSWORD` are your Apple ID and your App Specific Password for App Store Connect.

`APPLE_TEAM_ID` is your Developer Team ID. You can find it [here](https://developer.apple.com/account/).

[Open this link](https://developer.apple.com/account/resources/identifiers/list) to register `NAMING_APP_ID`. Click on plus near `Identifiers` and follow instructions after it. `NAMING_APP_ID` is used for builds on other platforms, too.

To get values of the other secrets, follow these steps ([src1](https://developer.apple.com/help/account/create-certificates/create-developer-id-certificates), [src2](https://ioscodesigning.com/exporting-code-signing-files/#exporting-manually)):

1. [Open this link](https://developer.apple.com/account/resources/certificates/list)
2. Click the plus near "Certificates"
3. Select "Developer ID Certificate", press "Continue"
4. Open Keychain Access on your Mac
5. Select "Keychain Access" - "Certificate Assistant" - "Request a Certificate from a Certificate Authority"
6. Enter your email and choose key name, leave the last field empty
7. Click "Saved to disk", "Continue"
8. Load the just generated code signing request in the browser (the page opened after step 3)
9. Click "Continue"
10. Download the ".cer" certificate on your device
11. Click on it twice to import it to your Keychain
12. Enter "Keychain Access", select "login" on the left and category "My Certificates"
13. Find your new certificate, click on it and select "Export"
14. Select format ".p12"
15. Create a name and a password for your certificate in ".p12" format (password shouldn't be empty)
16. Export your certificate in ".p12" format
17. Run "base64 -w 0 path/to/your/certificate_in.p12" in terminal
18. Set secret `APPLE_CSC_LINK` (in your copy of this repository) as the output of the previous step
19. Set secret `APPLE_CSC_KEY_PASSWORD` as the password you created in step 15

## Build

After correctly setting 14 secrets as described above in your copy of this repository go to GitHub Actions page of your repository.

Run action `Check New Version` with option `Build the latest version anyway` on. It will build the latest version of Element Desktop with your homeserver. Installers will be added to Github Releases in your repository and to your storage.

Each day at 2:00 UTC your repository will check if new version of Element is available and will build it if required.

If you want to generate download links, run action `Generate Links` with version of Element you just build. These links would be added to the corresponding Release.
