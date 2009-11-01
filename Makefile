CC      = g++
CFLAGS  = -O2 -Wall -Winline
LDFLAGS = 
OBJS    = nn.o sample.o
TARGET  = sample

all: clean sample

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) -O2 -Wall -c $<

nn.o: nn.cpp

tags:
	ctags -R

clean:
	rm -f *.o $(TARGET)

