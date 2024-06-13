#include <inttypes.h>  // https://stackoverflow.com/questions/12120426/how-do-i-print-uint32-t-and-uint16-t-variables-value
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "ntp.h"

#include <assert.h>

void debug_print_ntp_timetag(ntp_timetag* tt) {
  fprintf(stderr, "DEBUG: NTP(sec=%" PRIu32 " frac=%" PRIu32 ")\n", tt->sec,
          tt->frac);
}

void debug_print_timeval(struct timeval* tv) {
  fprintf(stderr, "DEBUG: Timeval(sec=%ld usec=%ld)\n", tv->tv_sec,
          tv->tv_usec);
}

void debug_print_timespec(struct timespec* ts) {
  fprintf(stderr, "DEBUG: Timespec(sec=%ld nsec=%ld)\n", ts->tv_sec,
          ts->tv_nsec);
}

bool double_cmp(double a, double b, double threshold) {
  if ((fabs(a) - fabs(b)) < threshold) {
    return true;
  }
  return false;
}

void test_timestamp_to_ntp_timetag(void) {
  // python:
  // timestamp = datetime.datetime(2020,1,1,1,1,1,123456,None).timestamp()
  double timestamp = 1577858461.123456;

  ntp_timetag tt;
  timestamp_to_ntp_timetag(timestamp, &tt);
  debug_print_ntp_timetag(&tt);

  assert(tt.sec == 3786847261);
  assert(tt.frac == 530239488);
}

void test_ntp_timetag_to_timestamp(void) {
  ntp_timetag tt;
  tt.sec = 3786847261;
  tt.frac = 530239488;

  double val = ntp_timetag_to_timestamp(&tt);
  double expected = 1577858461.123456;

  bool result = double_cmp(val, expected, 0.0000001);
  assert(result == true);
}

void test_timestamp_to_timeval(void) {
  double timestamp = 1577858461.123456;

  struct timeval tv;
  timestamp_to_timeval(timestamp, &tv);

  debug_print_timeval(&tv);

  assert(tv.tv_sec == 1577858461);
  assert(tv.tv_usec == 123456);
}

void test_timeval_to_timestamp(void) {
  double expected = 1577858461.123456;
  struct timeval tv;

  tv.tv_sec = 1577858461;
  tv.tv_usec = 123456;

  double result = timeval_to_timestamp(&tv);
  fprintf(stderr, "DEBUG: tv->tstmp: %.6f\n", result);

  assert(expected == result);
}

void test_timespec_to_timestamp(void) {
  double expected = 1577858461.123456;
  struct timespec ts;

  ts.tv_sec = 1577858461;
  ts.tv_nsec = 123456001;

  double result = timespec_to_timestamp(&ts);
  fprintf(stderr, "DEBUG: ts->tstmp: %.6f\n", result);

  assert(expected == result);
}

void test_timestamp_to_timespec(void) {
  double timestamp = 1577858461.123456;

  struct timespec ts;
  timestamp_to_timespec(timestamp, &ts);

  debug_print_timespec(&ts);

  assert(ts.tv_sec == 1577858461);
  assert(ts.tv_nsec == 123456001);  // precision issues from double maybe...
}

void test_ntp_timetag_to_timeval(void) {
  ntp_timetag tt;
  tt.sec = 3786847261;
  tt.frac = 530239488;

  struct timeval tv;
  ntp_timetag_to_timeval(&tt, &tv);

  assert(tv.tv_sec == 1577858461);
  assert(tv.tv_usec == 123456);
}

void test_ntp_timetag_to_timespec(void) {
  ntp_timetag tt;
  tt.sec = 3786847261;
  tt.frac = 530239488;

  struct timespec ts;
  ntp_timetag_to_timespec(&tt, &ts);

  debug_print_timespec(&ts);
  assert(ts.tv_sec == 1577858461);
  assert(ts.tv_nsec == 123456001);
}

void test_timeval_to_ntp_timetag(void) {
  struct timeval tv;
  tv.tv_sec = 1577858461;
  tv.tv_usec = 123456;

  ntp_timetag tt;
  timeval_to_ntp_timetag(&tv, &tt);
  debug_print_ntp_timetag(&tt);

  assert(tt.sec == 3786847261);
  assert(tt.frac >= 530239480);
}

void test_timespec_to_ntp_timetag(void) {
  struct timespec ts;
  ts.tv_sec = 1577858461;
  ts.tv_nsec = 123456001;

  ntp_timetag tt;
  timespec_to_ntp_timetag(&ts, &tt);
  debug_print_ntp_timetag(&tt);

  assert(tt.sec == 3786847261);
  assert(tt.frac >= 530239480);
}

int main(void) {
  test_timestamp_to_ntp_timetag();
  test_timestamp_to_timespec();
  test_timestamp_to_timeval();
  test_timeval_to_timestamp();
  test_ntp_timetag_to_timeval();
  test_ntp_timetag_to_timespec();
  test_timeval_to_ntp_timetag();
  test_timespec_to_ntp_timetag();

  return 0;
}
