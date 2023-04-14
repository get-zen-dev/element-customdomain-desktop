# chs-element-desktop

This repo builds [Element Desktop](https://github.com/vector-im/element-desktop) with custom home server.

Action [Build And Deploy](./.github/workflows/build_and_deploy.yaml) can be run manually with specifying OS, homeserver and Element version.

Action [Check New Versions](./.github/workflows/check_date.yaml) runs on schedule and builds the latest version of Element (if it was released after the previous run of this action) for all OS with our homeserver.
