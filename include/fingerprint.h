#ifndef FINGER_PRINT_H_
#define FINGER_PRINT_H_

int initialize_fingerprint_sensor();
int enroll_fingerprint(int staff_id);
int verify_fingerprint(int staff_id);
void cleanup_fingerprint_sensor();

#endif // FINGER_PRINT_H_