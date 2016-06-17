package red;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Wall {
	public short distanceFromCenter, side, length;
	public Wall(short side, short distanceFromCenter, short length) {
		this.side = side;
		this.distanceFromCenter = distanceFromCenter;
		this.length = length;
	}
	
	/**
	 * WARNING This will auto cast an int to a short!
	 * @param side
	 * @param distanceFromCenter
	 * @param length
	 */
	public Wall(int side, int distanceFromCenter, int length) {
		this.side = (short)side;
		this.distanceFromCenter = (short)distanceFromCenter;
		this.length = (short)length;
	}
	
	public Wall(FileInputStream file) throws UnsupportedOperationException {
		try {
			byte[] data = new byte[3 * 2];
			file.read(data, 0, 3 * 2);
			ByteBuffer bb = ByteBuffer.wrap(data);
			bb.order(ByteOrder.LITTLE_ENDIAN);
			side = bb.getShort();
			distanceFromCenter = bb.getShort();
			length = bb.getShort();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void writeObject(FileOutputStream file) {
		ByteBuffer bb = ByteBuffer.allocate(3 * 2);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putShort(side);
		bb.putShort(distanceFromCenter);
		bb.putShort(length);
		try {
			file.write(bb.array());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
