#ifndef LIBAII_LIBRARY_H
#define LIBAII_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

enum Status {
    SUCCESS = 0,
    ERROR,
};

/**
 * Install file
 * @param src - file to install
 * @param dest - destination
 * @return result
 */
enum Status install(const char* src, const char* dest);

/**
 * Generate .desktop file
 * @param output name for .desktop file
 * @param name name of app
 * @param exec application binary
 * @param terminal run in terminal
 * @param type application type
 * @param icon path to icon
 * @param comment comment for application
 * @param categories application categories
 *
 * @return result
 */
enum Status generateDesktop(
    const char* output, const char *name, const char* exec,
    int terminal, const char* type, const char* icon,
    const char* comment, const char* categories);

#ifdef __cplusplus
}
#endif

#endif // LIBAII_LIBRARY_H