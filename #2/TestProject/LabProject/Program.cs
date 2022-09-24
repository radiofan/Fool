using System;
using System.Collections.Generic;

namespace LabProject {
	public class Program {
		static void Main(string[] args) {
			Console.WriteLine("RADIOFAN");
		}

		public static Decimal fibonachchi(byte ind){
			if(ind == 0)
				return 0;
			if(ind == 1)
				return 1;
			
			Decimal first = 0, second = 1;
			for(byte i = 2; i <= ind; i++){
				second += first;
				first = second - first;
			}
			return second;
		}

		public static Decimal[] simple(int limit){
			List<Decimal> ret = new List<Decimal>();
			bool[] numbers = new bool[limit];
			for(int i=0; i<limit; i++){
				numbers[i] = true;
			}
			
			for(int i=2; i*i<=limit; i++){
				if(!numbers[i-1])
					continue;

				for(int a=i*i; a<=limit; a+=i){
					numbers[a-1] = false;
				}
			}

			for(int i=0; i<limit; i++){
				if(numbers[i])
					ret.Add(i+1);
			}
			
			return ret.ToArray();
		}

		public static int high_bit_number(UInt64 x){
			int ret = -1;
			while(x!=0){
				ret++;
				x >>= 1;
			}
			return ret;
		}

		public static string draw_sandglass(UInt32 h, UInt32 w){

			string str = "";
			if(h == 0 || w == 0)
				return str;

			char[][] tmp_matrix = new char[h][];

			UInt32 y_lim = h/2 + h % 2;
			UInt32 x_lim = w/2 + w % 2;
			UInt32 tmp;
			for(UInt32 y=0; y<y_lim; y++){
				tmp_matrix[y] = new char[w];
				for(UInt32 x=0; x<x_lim; x++){
					if(x < y){
						tmp_matrix[y][x] = ' ';
					}else{
						tmp_matrix[y][x] = '*';
					}
					tmp = w - 1 - x;
					if(tmp != x){
						tmp_matrix[y][tmp] = tmp_matrix[y][x];
					}
				}
				tmp = h - 1 - y;
				if(tmp != y){
					tmp_matrix[tmp] = tmp_matrix[y];
				}
			}

			for(UInt32 y=0; y<h; y++){
				for(UInt32 x=0; x<w-1; x++){
					str += tmp_matrix[y][x];
				}
				str += tmp_matrix[y][w-1] + "\r\n";
			}


			return str;
		}

		public static string parent_str(string first, string second){

			string big = (first.Length > second.Length ? first : second);
			string small = (first.Length <= second.Length ? first : second);
			if(small.Length == 0){
				return big;
			}

			Int32 overlap_big_start = 0, overlap_small_start = 0, overlap_len = 0;
			for(Int32 big_ind = big.Length-1, small_ind = 0, len = 1; small_ind < small.Length;){
				if(big.Substring(big_ind, len) == small.Substring(small_ind, len) && len > overlap_len){
					overlap_big_start = big_ind;
					overlap_small_start = small_ind;
					overlap_len = len;
					if(len == small.Length){
						break;
					}
				}
		
				//инкременты
				if(big_ind > 0){
					big_ind--;
					if(len < small.Length)
						len++;
				}else{
					small_ind++;
					len--;
				}
			}
	
			if(overlap_len == small.Length){
				return big;
			}else if(overlap_small_start > 0){
				return small + big.Substring(overlap_big_start + overlap_len);
			}else{
				return big + small.Substring(overlap_small_start + overlap_len);
			}
		}

		public static bool is_palindrom(string str){
			for(int i=0; i<str.Length / 2; i++){
				if(str[i] != str[str.Length - 1 - i])
					return false;
			}
			return true;
		}

		public static int palindrom_count(string str){
			if(is_palindrom(str)){
				return 1;
			}else{
				int min = str.Length;
				int tmp;
				for(int i = 1; i < str.Length; i++){
					tmp = palindrom_count(str.Substring(0, i)) + palindrom_count(str.Substring(i, str.Length - i));
					if(tmp < min)
						min = tmp;
				}
				return min;
			}
		}

		public static bool is_odd(int x){
			return (x & 0x01) == 0x01;
		}
		public static bool is_even(int x){
			return (x & 0x01) == 0x00;
		}

		public static int sign(Int32 x){
			if(x == 0)
				return 0;
            return (x & 0x80000000) == 0 ? 1 : -1;
		}
	}
}
