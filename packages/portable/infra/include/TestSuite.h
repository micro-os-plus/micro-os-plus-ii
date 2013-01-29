/*       Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_INFRA_TESTSUITE_H_
#define OS_PORTABLE_INFRA_TESTSUITE_H_

#include <stdint.h>
#include <unistd.h>

namespace os
{
  namespace infra
  {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"

    class TestSuite
    {
    public:

      typedef uint8_t LineType_t;
      class LineType
      {
      public:
        const static LineType_t START = 1;
        const static LineType_t INFO = 2;
        const static LineType_t PASS = 3;
        const static LineType_t FAIL = 4;
        const static LineType_t STOP = 5;
      };

      TestSuite();
      ~TestSuite();

      // This method must be implemented by the test user
      void
      run(void);

      void
      setClassName(const char* pName);

      void
      start(const char* pMessage) const;
      void
      check(bool expression, const char* pMessage);
      void
      pass(const char* pMessage);
      void
      fail(const char* pMessage);
      void
      info(const char* pMessage) const;
      void
      stop(const char* pMessage) const;

      void
      parseParameters(int argc, char* argv[]);

      int
      getExitValue(void) const;

    private:

      void
      output(LineType_t lineType, const char* pMessage) const;

      void
      outXml(bool isFailure, const char* pMessage);

      ssize_t
      writeStringToFile(const char* pString) const;

      ssize_t
      putString(const char* pString) const;

      void
      putNumber(int n) const;

      void
      putNewLine(void) const;

      const char* pClassName;

      int countPassed;
      int countFailed;

      int xmlFileDescriptor;

    };
    /* class TestSuite */

#pragma GCC diagnostic push

    inline void
    TestSuite::setClassName(const char* pName)
    {
      this->pClassName = pName;
    }

  } /* namespace infra */
} /* namespace os */

#endif /* #define OS_PORTABLE_INFRA_TESTSUITE_H_ */
