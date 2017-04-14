Vulkan API samples
==================

Demonstrates basic usages of Vulkan APIs.

Introduction
------------
The project includes series of samples demonstrating a basic usage of Vulkan APIs.
This repository is a replication of [LunarG sample kit](https://github.com/LunarG/VulkanSamples), refer to [wiki](https://github.com/googlesamples/vulkan-basic-samples/wiki) for more background.

Getting Started
---------------
Refer [Getting Started Guide](http://developer.android.com/ndk/guides/graphics/getting-started.html).

Screenshots
-----------
![screenshot](image/screen.png)


## Prerequisites
- Android Studio 2.3.0 or later.
- Android SDK N-preview or later
- NDK r12 beta or later

## Sample Import
To import the samples, follow steps below:

### Step 1: Build shaderc in NDK.
In a command-prompt navigate to “${ndk_root}/sources/third_party/shaderc”
Run the following command

~~~
../../../ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_STL:=gnustl_static APP_ABI=[armeabi-v7a|arm64-v8a|x86|x86_64|all] libshaderc_combined -j16
~~~

APP_STL can be one of gnustl_static, gnustl_shared, c++_static, c++_shared.
Here, it’s going to use statically linked version of gnustl port as samples are using it.

### Step 2: Import the samples into Android Studio with one of the following methods:
* Import Android Code Sample: choose "Import and Android code sample", search and select "Vulkan API samples". Android Studio will download sample code directly from github.
* Import project: choose “Import project (Eclipse, ADT, Gradle)” and select `build.gradle` locating at the root of your repo directory

Note:  the project include 40+ subjects, takes some time to load, specially for Windows OS

Support
-------

- Google+ Community: https://plus.google.com/communities/<...>
- Stack Overflow: http://stackoverflow.com/questions/tagged/<...>

If you've found an error in this sample, please file an issue:
https://github.com/googlesamples/<...>/issues

Patches are encouraged, and may be submitted by forking this project and
submitting a pull request through GitHub.

License
-------

Copyright 2016 Google, Inc.

Licensed to the Apache Software Foundation (ASF) under one or more contributor
license agreements.  See the NOTICE file distributed with this work for
additional information regarding copyright ownership.  The ASF licenses this
file to you under the Apache License, Version 2.0 (the "License"); you may not
use this file except in compliance with the License.  You may obtain a copy of
the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
License for the specific language governing permissions and limitations under
the License.
