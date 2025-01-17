/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <folly/io/async/EventBase.h>

namespace std {
class thread;
}

namespace folly {

/**
 * A helper class to start a new thread running a TEventBase loop.
 *
 * The new thread will be started by the ScopedEventBaseThread constructor.
 * When the ScopedEventBaseThread object is destroyed, the thread will be
 * stopped.
 */
class ScopedEventBaseThread {
 public:
  explicit ScopedEventBaseThread(bool autostart = true);
  ~ScopedEventBaseThread();

  ScopedEventBaseThread(ScopedEventBaseThread&& other) noexcept;
  ScopedEventBaseThread &operator=(ScopedEventBaseThread&& other) noexcept;

  /**
   * Get a pointer to the TEventBase driving this thread.
   */
  EventBase* getEventBase() const {
    return eventBase_.get();
  }

  void start();
  void stop();
  bool running();

 private:
  ScopedEventBaseThread(const ScopedEventBaseThread& other) = delete;
  ScopedEventBaseThread& operator=(const ScopedEventBaseThread& other) = delete;

  std::unique_ptr<EventBase> eventBase_;
  std::unique_ptr<std::thread> thread_;
};

}
