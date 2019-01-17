package main.java.codility.stackQueue;

public class Fish implements Comparable<Fish> {
	int size;
	FishDirection direction;

	public Fish(int s, FishDirection fd) {
		size = s; direction = fd;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	//////////////////////////////////
	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		this.size = size;
	}

	public FishDirection getDirection() {
		return direction;
	}

	public void setDirection(FishDirection direction) {
		this.direction = direction;
	}

	@Override
	public int compareTo(Fish o) {
		if (this.getSize() > o.getSize()) return 1;
		if (this.getSize() == o.getSize()) return 0;
		return -1;
	}
	
}
