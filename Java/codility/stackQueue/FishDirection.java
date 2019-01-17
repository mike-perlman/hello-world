package main.java.codility.stackQueue;

public enum FishDirection {
UPSTREAM,
DOWNSTREAM;

public static FishDirection fromInt(int i) {
	if (i > 0) return DOWNSTREAM;
	return UPSTREAM;
}
}
