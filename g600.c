#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

struct input_event events[64];
const char kDir[] = "/dev/input/by-id/";
const char kPrefix[] = "usb-Logitech_Gaming_Mouse_G600_";
const char kSuffix[] = "-if01-event-kbd";

// ADD KEY->COMMAND MAPPINGS HERE:
const char *downCommands[] = {
  // //[scancode] = "command to run",
  // [4] = "xdotool key Page_Up", // scroll left
  // [5] = "xdotool key Page_Down", // scroll right
  // [6] = "xdotool key ctrl+c", // G8
  // [7] = "xdotool key ctrl+shift+c", // G7
  // [8] = "i3-msg workspace next_on_output", // G9
  // [9] = "i3-msg move workspace next_on_output", // G10
  // [10] = "xdotool key ctrl+w", // G11
  // [11] = "pulseaudio-ctl down", // G12
  // [12] = "pulseaudio-ctl mute", // G13
  // [13] = "xdotool key ctrl+z", // G14
  // [14] = "xdotool key End", // G15
  // [15] = "xdotool key ctrl+End", // G16
  // [16] = "xdotool key Return", // G17
  // [17] = "i3-msg fullscreen", // G18
  // [18] = "xdotool key ctrl+slash t", // G19
  // [19] = "", // G20
  // [20] = "xdotool key alt+Left", // G-shift + scroll left
  // [21] = "xdotool key alt+Right", // G-shift + scroll right
  // [22] = "xdotool key ctrl+v", // G-shift + G8
  // [23] = "xdotool key ctrl+shift+v", // G-shift + G7
  // [24] = "i3-msg workspace prev_on_output", // G-shift + G9
  // [25] = "i3-msg move workspace prev_on_output", // G-shift + G10
  // [26] = "i3-msg kill", // G-shift + G11
  // [27] = "pulseaudio-ctl up", // G-shift + G12
  // [28] = "pulseaudio-ctl mute", // G-shift + G13
  // [29] = "xdotool key ctrl+shift+z ctrl+y", // G-shift + G14
  // [30] = "xdotool key Home", // G-shift + G15
  // [31] = "xdotool key ctrl+Home", // G-shift + G16
  // [32] = "xdotool key Escape", // G-shift + G17
  // [33] = "i3-msg fullscreen", // G-shift + G18
  // [34] = "", // G-shift + G19
  // [35] = "", // G-shift + G20
  // [37] = "echo button down"

  // REGULAR KEYS
  [30] = "xdotool key l+m+a+o", // G9
  [31] = "xdotool key ctrl+w", // G10
  [32] = "xdotool key ctrl+f", // G11
  [33] = "xdotool key ctrl+v", // G12
  [34] = "xdotool key Super+Left", // G13
  [35] = "xdotool key ctrl+t", // G14
  [36] = "xdotool key ctrl+c", // G15
  [37] = "xdotool key Super+Right", // G16
  [38] = "xdotool key Super+Up", // G17
  [46] = "xdotool key F11", // G18
  [56] = "xdotool key F10", // G19
  [48] = "xdotool key F5", // G20
  
  [54] = "xdotool key ctrl+n", // G7
  [49] = "xdotool key End", // Wheel Right
  [47] = "xdotool key Home", // Wheel Left

  // G-SHIFT KEYS
  [5] = "xdotool key Super+1", // G-Shift G9
  [4] = "xdotool key Super+2", // G-Shift G10
  [11] = "xdotool key Super+3", // G-Shift G11
  [6] = "xdotool key ctrl+shift+v", // G-Shift G12
  [10] = "xdotool key ctrl+Page_Up", // G-Shift G13
  [12] = "xdotool key ctrl+shift+t", // G-Shift G14
  [7] = "xdotool key ctrl+shift+c", // G-Shift G15
  [9] = "xdotool key ctrl+Page_Down", // G-Shift G16
  [13] = "xdotool key Super+Down", // G-Shift G17
  [8] = "", // G-Shift G18
  [15] = "", // G-Shift G19
  [14] = "xdotool key Enter", // G-Shift G20
  
  [21] = "xdotool key ctrl+shift+n", // G-Shift G7
  [28] = "", // G-Shift Wheel Right
  [29] = "" // G-Shift Wheel Left

};
const char *upCommands[] = {
  //[scancode] = "command to run",
  [37] = "echo button up"
};

int starts_with(const char* haystack, const char* prefix) {
  size_t prefix_length = strlen(prefix), haystack_length = strlen(haystack);
  if (haystack_length < prefix_length) return 0;
  return strncmp(prefix, haystack, prefix_length) == 0;
}

int ends_with(const char* haystack, const char* suffix) {
  size_t suffix_length = strlen(suffix), haystack_length = strlen(haystack);
  if (haystack_length < suffix_length) return 0;
  size_t haystack_end = haystack + haystack_length - suffix_length;
  return strncmp(suffix, haystack_end, suffix_length) == 0;
}

// Returns non-0 on error.
int find_g600(char *path) {
  //*path = kDir;
  DIR *dir;
  struct dirent *ent;
  if (!(dir = opendir(kDir))) {
    return 1;
  }
  while ((ent = readdir(dir))) {
    if (starts_with(ent->d_name, kPrefix) && ends_with(ent->d_name, kSuffix)) {
      strcpy(path, kDir);
      strcat(path, ent->d_name);

      printf("full path is %s\n", path);

      //*path += ent->d_name;
      closedir(dir);
      return 0;
    }
  }
  closedir(dir);
  return 2;
}

int main() {
  printf("Starting G600 Linux controller.\n\n");
  printf("It's a good idea to configure G600 with Logitech Gaming Software before running this program:\n");
  printf(" - assign left, right, middle mouse button and vertical mouse wheel to their normal functions\n");
  printf(" - assign the G-Shift button to \"G-Shift\"\n");
  printf(" - assign all other keys (including horizontal mouse wheel) to arbitrary (unique) keyboard keys\n");
  printf("\n");    
  char path[1024];
  int find_error = find_g600(&path);
  if (find_error) {
    printf("Error: Couldn't find G600 input device.\n");
    switch(find_error) {
    case 1: 
      printf("Suggestion: Maybe the expected directory (%s) is wrong. Check whether this directory exists and fix it by editing \"g600.c\".\n", kDir);
      break;
    case 2:
      printf("Suggestion: Maybe the expected device prefix (%s) is wrong. Check whether a device with this prefix exists in %s and fix it by editing \"g600.cpp\".\n", kPrefix, kDir);
      break;
    }
    printf("Suggestion: Maybe a permission is missing. Try running this program with with sudo.\n");
    return 1;
  }
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    printf("Error: Couldn't open \"%s\" for reading.\n", path);
    printf("Reason: %s.\n", strerror(errno));
    printf("Suggestion: Maybe a permission is missing. Try running this program with with sudo.\n");
    return 1;
  }

  ioctl(fd, EVIOCGRAB, 1);
  printf("G600 controller started successfully.\n\n");
  while (1) {
    size_t n = read(fd, events, sizeof(events));
    if (n <= 0) return 2;
    if (n < sizeof(struct input_event) * 2) continue;
    if (events[0].type != 4) continue;
    if (events[0].code != 4) continue;
    if (events[1].type != 1) continue;
    int pressed = events[1].value;
    int scancode = events[0].value & ~0x70000;

    const char* actionStr = (pressed) ? "Pressed" : "Released";
    printf("%s scancode %d.\n",actionStr, scancode);

    const char *downCommand = downCommands[scancode], *upCommand = upCommands[scancode];
    const char *cmdToRun = (pressed) ? downCommand : upCommand;
    if (!cmdToRun || !strlen(cmdToRun)) continue;

    printf("Executing: \"%s\"\n", cmdToRun);
    system(cmdToRun);
    printf("\n");
  }
  
  close(fd);
}
