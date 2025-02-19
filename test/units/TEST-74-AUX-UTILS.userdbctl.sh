#!/usr/bin/env bash
# SPDX-License-Identifier: LGPL-2.1-or-later
set -eux
set -o pipefail

# shellcheck source=test/units/util.sh
. "$(dirname "$0")"/util.sh

# Make sure that -F shows same data as if we'd ask directly
userdbctl user root -j | userdbctl -F- user  | cmp - <(userdbctl user root)
userdbctl user systemd-network -j | userdbctl -F- user  | cmp - <(userdbctl user systemd-network)
userdbctl user 65534 -j | userdbctl -F- user  | cmp - <(userdbctl user 65534)

userdbctl group root -j | userdbctl -F- group  | cmp - <(userdbctl group root)
userdbctl group systemd-network -j | userdbctl -F- group  | cmp - <(userdbctl group systemd-network)
userdbctl group 65534 -j | userdbctl -F- group  | cmp - <(userdbctl group 65534)
