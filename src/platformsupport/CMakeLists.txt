# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT WASM)
    add_subdirectory(devicediscovery)
    add_subdirectory(fbconvenience)
endif()
if(QT_FEATURE_evdev OR QT_FEATURE_integrityhid OR QT_FEATURE_libinput OR QT_FEATURE_tslib OR QT_FEATURE_xkbcommon OR QT_FEATURE_vxworksevdev)
    add_subdirectory(input)
endif()
if(QT_FEATURE_kms)
    add_subdirectory(kmsconvenience)
endif()
