package main.java.codility.stackQueue;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Stack;
import java.util.Deque;
import java.util.List;

public class VoraciousFish {

	List<Fish> river = new ArrayList<Fish>();
	List<Deque<Fish>> buckets = new ArrayList<Deque<Fish>>();

	public VoraciousFish(int sizes[], int directions[], int len) {
		Deque<Fish> currentBucket = new ArrayDeque<Fish>();
		Fish f = new Fish(sizes[0], FishDirection.fromInt(directions[0]));
		currentBucket.push(f);
		
		//load them up -- create new bucket on direction change.
		for(int i = 1; i < len; i++) {
			f = new Fish(sizes[i], FishDirection.fromInt(directions[i]));

			if (currentBucket.peek().getDirection() != f.getDirection()) {
				buckets.add(currentBucket);
				currentBucket = new ArrayDeque<Fish>();
			}
			
			//queue or stack, based on direction (they'll be popped during contests)
			if (f.getDirection()== FishDirection.UPSTREAM)
				currentBucket.addLast(f);
			else
				currentBucket.addFirst(f);
		}
		
		buckets.add(currentBucket);
	}
	////////////////////////////////////
	/**
	 * 1) peel off starting and ending buckets of fish, which "swam" off the head and tail. 
	 * 2) Resolve conflicts internally, removing empty buckets after each fight.
	 * @return the number of fish which survived.
	 */
	private int resolveTurn() {
		int out = 0;
		while(!buckets.isEmpty() && buckets.get(0).peek().getDirection() == FishDirection.UPSTREAM) {
			out += buckets.get(0).size();
			buckets.remove(0);
		}
		while(!buckets.isEmpty() && buckets.get(buckets.size()-1).peek().getDirection() == FishDirection.DOWNSTREAM) {
			out += buckets.get(buckets.size()-1).size();
			buckets.remove(buckets.size()-1);
		}
		
		//either we have no buckets or we have opposing fish.
		if (buckets.isEmpty()) return out;
		
		for (int i = 0; i < buckets.size()-1; i++) {
			int current = i;
			int next = i+1;
			if (buckets.get(current).peek().getDirection() != buckets.get(next).peek().getDirection()) {
				while(current >= 0 && next < buckets.size() 
						&& buckets.get(current).peek().getDirection() != buckets.get(next).peek().getDirection()) {
					contest(buckets.get(current), buckets.get(next));
					if (buckets.get(next).isEmpty()) buckets.remove(next);
					if (buckets.get(current).isEmpty()) buckets.remove(current);
				}
			}
		}
		return out;
	}
	
	/**
	 * iterates over the river until all fish are either eaten or swam away.
	 * @return
	 */
	public int resolveGame() {
		int out = 0;
		while(!buckets.isEmpty()) {
			out += resolveTurn();
		}
		return out;
	}
	
	/**
	 * larger fish (by size) wins.  Loser gets popped.
	 * @param a
	 * @param b
	 */
	private void contest(Deque<Fish> a, Deque<Fish>b) {
		while (a.size() > 0  && b.size() > 0) {
			if (a.peek().getSize() > b.peek().getSize())
				b.pop();
			else
				a.pop();
		}
	}
/////////////////////////////////////////////////////////
	
	public static void main(String[] args) {
		int a[] = {4,3,11,8,2,1,5,9,10};
		int b[] = {0,1,1,1,0,0,0,0,0};
		VoraciousFish vf = new VoraciousFish(a,b,a.length);
		int survivors = vf.resolveGame();
		System.out.print("Starting board: [ ");
		for (int x : a) {System.out.print(x + " ");}
		System.out.println("].  Surviving fish=["+ survivors + "]");
		}

}
