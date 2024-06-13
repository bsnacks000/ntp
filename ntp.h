/**
 * @file ntp.h
 * @author bsnacks000
 * @brief ntp conversion utilities.
 * @version 0.1.0
 *
 */
#ifndef __NTP__H__
#define __NTP__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>
#include <time.h>

// n timestamp between 1/1/1900 (ntp base) and unix epoch (1/1/1970)
#define NTPTIME_1_JAN1970 2208988800

typedef struct {
  uint32_t sec;
  uint32_t frac;

} ntp_timetag;

// ntp -> (timeval, timespec, timestamp)

void ntp_timetag_to_timeval(ntp_timetag* tt, struct timeval* tv);

void ntp_timetag_to_timespec(ntp_timetag* tt, struct timespec* ts);

double ntp_timetag_to_timestamp(ntp_timetag* tt);

// timeval -> (ntp, timestamp)

void timeval_to_ntp_timetag(struct timeval* tv, ntp_timetag* tt);

double timeval_to_timestamp(struct timeval* tv);

// timespec -> (ntp, timestamp)

void timespec_to_ntp_timetag(struct timespec* ts, ntp_timetag* tt);

double timespec_to_timestamp(struct timespec* ts);

// timestamp (ntp, timespec, timeval)

void timestamp_to_timeval(double sec, struct timeval* tv);

void timestamp_to_timespec(double sec, struct timespec* ts);

void timestamp_to_ntp_timetag(double sec, ntp_timetag* tt);

#ifdef __cplusplus
}
#endif

#endif  //!__NTP__H__
