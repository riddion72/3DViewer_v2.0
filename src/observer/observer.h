#ifndef CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_
#define CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_

#include <iostream>

#include "../view/settings.h"

namespace s21 {

/**
 * @class Observer
 * @brief An abstract class representing an observer that can be notified of
 * changes in settings.
 */
class Observer {
 public:
  /// @brief Virtual destructor
  virtual ~Observer(){};

  /// @brief Virtual function to set options based on the provided settings
  /// @param options The Settings object containing configuration options
  virtual void setOptions(Settings options) = 0;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_
