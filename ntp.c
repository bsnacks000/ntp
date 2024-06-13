#include "ntp.h"

#include <stdio.h>
// https://tickelton.gitlab.io/articles/ntp-timestamps/

#define DOUBLE_POW_2_32 (double)(1LL << 32)

void ntp_timetag_to_timeval(ntp_timetag* tt, struct timeval* tv) {
  tv->tv_sec = tt->sec - NTPTIME_1_JAN1970;
  tv->tv_usec = (uint32_t)((double)tt->frac * 1.0e6 / DOUBLE_POW_2_32);
}

void ntp_timetag_to_timespec(ntp_timetag* tt, struct timespec* ts) {
  ts->tv_sec = tt->sec - NTPTIME_1_JAN1970;
  ts->tv_nsec = (uint32_t)((double)tt->frac * 1.0e9 / DOUBLE_POW_2_32);
}

void timeval_to_ntp_timetag(struct timeval* tv, ntp_timetag* tt) {
  tt->sec = tv->tv_sec + NTPTIME_1_JAN1970;
  tt->frac = (uint32_t)((double)(tv->tv_usec) * DOUBLE_POW_2_32 * 1.0e-6);
}

void timespec_to_ntp_timetag(struct timespec* ts, ntp_timetag* tt) {
  tt->sec = ts->tv_sec + NTPTIME_1_JAN1970;
  tt->frac = (uint32_t)((double)(ts->tv_nsec) * DOUBLE_POW_2_32 * 1.0e-9);
}

// these are based on osc4py3.buildparse

double ntp_timetag_to_timestamp(ntp_timetag* tt) {
  return (double)(tt->sec - NTPTIME_1_JAN1970) +
         ((double)tt->frac / DOUBLE_POW_2_32);
}

void timestamp_to_ntp_timetag(double sec, ntp_timetag* tt) {
  sec += (double)NTPTIME_1_JAN1970;
  tt->sec = (uint32_t)sec;
  tt->frac = (uint32_t)((sec - (double)tt->sec) * DOUBLE_POW_2_32 + 0.5);
}

// https://www.cs.columbia.edu/~hgs/research/projects/NetworkAudioLibrary/rtp/rtplib-1.0b2/example1.c

double timeval_to_timestamp(struct timeval* tv) {
  return tv->tv_sec + (tv->tv_usec / 1.e6);
}

double timespec_to_timestamp(struct timespec* ts) {
  return ts->tv_sec + (ts->tv_nsec / 1.e9);
}

void timestamp_to_timeval(double sec, struct timeval* tv) {
  tv->tv_sec = (uint32_t)sec;
  tv->tv_usec = (uint32_t)((sec - (uint32_t)sec) * 1.e6);
}

void timestamp_to_timespec(double sec, struct timespec* ts) {
  ts->tv_sec = (uint32_t)sec;
  ts->tv_nsec = (uint32_t)((sec - (uint32_t)sec) * 1.e9);
}
