#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100
#define SONG_DURATION 3
char* queue[MAX];
int front = -1, rear = -1;
char* currentSong = NULL;

void readString(char* buffer, int size) {
fgets(buffer, size, stdin);
size_t len = strlen(buffer);
if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}
void enqueue(char* song) {
if (rear == MAX - 1) {
printf("❌ Queue is full!\n");
return;
}
if (front == -1) front = 0;
queue[++rear] = strdup(song);
printf("✅ Added \"%s\" to queue.\n", song);
}
char* dequeue() {
if (front == -1 || front > rear) {
printf("❌ Queue is empty!\n");
return NULL;
}
return queue[front++];
}
void showQueue() {
printf("\n🎶 Current Queue:\n");
if (front == -1 || front > rear) {
printf("Queue is empty.\n");
return;
}
for (int i = front; i <= rear; i++) {
printf("%d. %s\n", i - front + 1, queue[i]);
}
}
void shuffleQueue() {

10

if (front == -1 || front >= rear) {
printf("Need at least 2 songs to shuffle.\n");
return;
}
srand(time(NULL));
for (int i = rear; i > front; i--) {
int j = front + rand() % (i - front + 1);
char* temp = queue[i];
queue[i] = queue[j];
queue[j] = temp;
}
printf("🔀 Queue shuffled!\n");
}
void removeSong(char* name) {
int found = 0;
for (int i = front; i <= rear; i++) {
if (strcmp(queue[i], name) == 0) {
free(queue[i]);
for (int j = i; j < rear; j++) {
queue[j] = queue[j + 1];
}
rear--;
found = 1;
printf("❌ Removed \"%s\" from queue.\n", name);
break;
}
}
if (!found) {
printf("⚠ Song not found in queue.\n");
}
}

void showStats() {
int count = (front == -1 || front > rear) ? 0 : (rear - front + 1);
printf("🎵 %d song(s) in queue.\n", count);
printf("🕒 Estimated play time: %d minutes\n", count * SONG_DURATION);
}
void showPlayerUI() {
printf("\n┌──────────────────────────────┐\n");
printf("│ 🎵 Music Player │\n");
printf("├──────────────────────────────┤\n");
if (currentSong) {
printf("│ ▶ Now Playing: %-16s │\n", currentSong);
} else {
printf("│ ▶ Now Playing: [None] │\n");
}

11

printf("├──────────────────────────────┤\n");
printf("│ Controls: │\n");
printf("│ 1. ➕ Add song to queue │\n");
printf("│ 2. ⏭ Play next song │\n");
printf("│ 3. 🔁 Repeat current song │\n");
printf("│ 4. 📂 Show queue │\n");
printf("│ 5. 🔀 Shuffle queue │\n");
printf("│ 6. ❌ Remove song by name │\n");
printf("│ 7. 📊 Queue stats │\n");
printf("│ 8. 🚪 Exit │\n");
printf("└──────────────────────────────┘\n");
}
int main() {
int choice;
char buffer[256];
while (1) {
showPlayerUI();
printf("Enter your choice: ");
scanf("%d", &choice);
getchar(); // Clear newline
switch (choice) {
case 1:
printf("Enter song name: ");
readString(buffer, sizeof(buffer));
enqueue(buffer);
break;
case 2:
currentSong = dequeue();
if (currentSong)
printf("▶ Now playing: %s\n", currentSong);
break;
case 3:
if (currentSong)
printf("🔁 Replaying: %s\n", currentSong);
else
printf("❌ No song to repeat!\n");
break;
case 4:
showQueue();
break;
case 5:
shuffleQueue();

12

break;
case 6:
printf("Enter song name to remove: ");
readString(buffer, sizeof(buffer));
removeSong(buffer);
break;
case 7:
showStats();
break;
case 8:
printf("👋 Exiting music player...\n");
for (int i = front; i <= rear; i++) free(queue[i]);
exit(0);
default:
printf("❌ Invalid choice!\n");
}
printf("\nPress Enter to continue...");
getchar();
system("clear"); }
return 0;
}