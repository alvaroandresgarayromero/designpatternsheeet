#ifndef APP_ASSERT_MANAGER_H
#define APP_ASSERT_MANAGER_H

#define AWS_DEMO_ASSERT(b, msg) if (!(b)) { std::cerr << msg; exit(1); }
#define ALWAYS_ASSERT 0

#endif //APP_ASSERT_MANAGER_H
