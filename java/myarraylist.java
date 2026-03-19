
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;


public class myarraylist {
	public static void main (String[] args) {
		ArrayList <Integer> nums = new ArrayList <> ();
		nums.add (6);
		nums.add (4);
		nums.add(12);
		nums.add (8);
		System.out.println (" Elements : " + nums);
		System.out.println(" Element at index 1 : " + nums.get(1));
		System.out.println(" Size of array: " + nums.size() );
		nums.set(2, 15);
		System.out.println(" Elements : " + nums);
		nums.remove(3);
		System.out.println(" Elements : " + nums);
		nums.add (2, 21);
		System.out.println(" Elements : " + nums);
		Iterator <Integer> it = nums.iterator ();
		System.out.println("Iterating through nums");
		while (it.hasNext()) {
			System.out.println(it.next());
		}
		Collections.sort(nums);
		System.out.println(" Elements : " + nums);

	}
}
