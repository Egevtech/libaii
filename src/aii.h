#ifndef LIBAII_LIBRARY_H
#define LIBAII_LIBRARY_H

enum InstallStatus {
    SUCCESS = 0,
    ERROR,
};

/**
 * Install file
 * @param src - file to install
 * @param dest - destination
 * @return result
 */
enum InstallStatus install(const char* src, const char* dest);

/**
 * Generate .desktop file
 * @param filename name for .desktop file
 * @param title name of app
 * @param descript app description
 * @param icon path to icon
 * @return result
 */
enum InstallStatus generateDesktop(const char* filename, const char* title, const char* descript, const char* icon);

#endif // LIBAII_LIBRARY_H