#!/usr/bin/env bash
# SPDX-License-Identifier: LGPL-2.1-or-later
set -eux
set -o pipefail

# shellcheck source=test/units/util.sh
. "$(dirname "$0")"/util.sh

cleanup() {
    set +e
    userdel -r test-74-userdbctl
    groupdel test-74-userdbctl
}

trap cleanup EXIT

systemd-sysusers - <<EOF
u test-74-userdbctl - "Test user for TEST-74-AUX-UTILS.userdbctl.sh" / /bin/bash
EOF

# Make sure that -F shows same data as if we'd ask directly
userdbctl user root -j | userdbctl -F- user  | cmp - <(userdbctl user root)
userdbctl user test-74-userdbctl -j | userdbctl -F- user  | cmp - <(userdbctl user test-74-userdbctl)
userdbctl user 65534 -j | userdbctl -F- user  | cmp - <(userdbctl user 65534)

userdbctl group root -j | userdbctl -F- group  | cmp - <(userdbctl group root)
userdbctl group test-74-userdbctl -j | userdbctl -F- group  | cmp - <(userdbctl group test-74-userdbctl)
userdbctl group 65534 -j | userdbctl -F- group  | cmp - <(userdbctl group 65534)
