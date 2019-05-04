namespace s1910092
{
    partial class NearestNeighbor
    {
        static void Main(string[] args)
        {
            //ランダムで(幅20-40f、高さ20-40f)空間を生成する
            SquareFrame demo1 = new SquareFrame().RandomCreat(20, 40, 20, 40)
            .Print()//Demo1-1.png
            //ランダムな(0-1f,0-1f,密度50%)ベジェ曲線を生成する
            .RandomAddPoint_Bezier(1f, 1f, 0.5f)
            .Print()//Demo1-2.png
            //ランダムな「X」点20個生成する(ノイズ)
            .RandomAddPoint_Point(20, MARK.X)
            .Print()//Demo1-3.png
            .Run_kNN(3)//k-NN(3-NN)を実行する
            .Print();//Demo1-4.png


            //(幅5f、高さ5f)空間を生成する(解像度0.2f)
            SquareFrame demo2 = new SquareFrame(5f, 5f, 0.2f)
            .Print()//Demo2-1.png
            .AddGivenPoint(0.2f, 0.2f, MARK.a)//座標(0.2f,0.2f)に「＠」を生成する
            .AddGivenPoint(2, 2, MARK.X)//座標(2,2)に「X」を生成する
            .AddGivenPoint(2, 4, MARK.a)//座標(2,4)に「＠」を生成する
            .AddGivenPoint(4, 2, MARK.a)//座標(4,2)に「＠」を生成する
            .AddGivenPoint(4, 4, MARK.X)//座標(4,4)に「X」を生成する
            .Print()//Demo2-2.png
            .Run_kNN(3)//k-NN(3-NN)を実行する
            .Print();//Demo2-3.png


            //(幅40f、高さ40f)空間を生成する(解像度default：1f)
            SquareFrame demo3 = new SquareFrame(40, 40)
            .Print()//Demo3-1.png
            //ランダムな(焦点間距離2-7f、半径6-9f、密度70%、＠)楕円区域を生成する
            .RandomAddPoint_Oval(2, 7, 6, 9, 0.7f, MARK.a)
            .RandomAddPoint_Oval(2, 7, 6, 9, 0.7f, MARK.X)//ランダム楕円*2
            .RandomAddPoint_Oval(2, 7, 6, 9, 0.7f, MARK.a)//ランダム楕円*3
            .RandomAddPoint_Oval(2, 7, 6, 9, 0.7f, MARK.X)//ランダム楕円*4
            .Print()//Demo3-2.png
            .Run_kNN(3)//k-NN(3-NN)を実行する
            .Print();//Demo3-3.png
        }
    }
}
namespace s1910092
{
    using System;
    using System.Linq;
    using System.Collections.Generic;
    partial class NearestNeighbor
    {
        enum MARK : byte { NULL, a, X, o, x }
        static private string[] STRINGS = { " -", " @", " X", " O", " x" };
        class SquareFrame
        {
            private float width_0;
            private float height_0;
            private float DISPLAY_RESOLUTION_F;
            private Random ran = new Random();
            public class Lattice
            {
                public MARK mark = MARK.NULL;
                public Vector coord;
                public Lattice next_lattice;
                public Lattice(Vector coord, Lattice next_lattice)
                {
                    this.coord = coord;
                    this.next_lattice = next_lattice;
                }
                public void Print()
                {
                    Console.Write(STRINGS[(int)mark]);
                }
                public void PrintLine()
                {
                    Console.WriteLine(STRINGS[(int)mark]);
                }
            }
            Lattice first_lattice;
            Lattice lattice_pointer = null;
            public Dictionary<Vector, Lattice> lattice_dic = new Dictionary<Vector, Lattice>();
            public List<Vector> givenpoint_list = new List<Vector>();
            public SquareFrame(float width, float height, float DISPLAY_RESOLUTION_F)
            {
                this.DISPLAY_RESOLUTION_F = DISPLAY_RESOLUTION_F;
                width_0 = width - DISPLAY_RESOLUTION_F;
                height_0 = height - DISPLAY_RESOLUTION_F;
                for (float j = 0f; j <= height_0; j = (float)Math.Round(j + DISPLAY_RESOLUTION_F, 2))
                {
                    for (float i = width_0; i >= 0f; i = (float)Math.Round(i - DISPLAY_RESOLUTION_F, 2))
                    {
                        if (lattice_pointer == null)
                        {
                            first_lattice = lattice_pointer = new Lattice(new Vector(i, j), null);
                        }
                        else
                        {
                            first_lattice = new Lattice(new Vector(i, j), lattice_pointer);
                            lattice_pointer = first_lattice;
                        }
                        lattice_dic.Add(new Vector(i, j), lattice_pointer);
                    }
                }
            }
            public SquareFrame(float width, float height) : this(width, height, 1f) { }
            public SquareFrame()
            {
                //pls "new SquareFrame().RandomCreat(...)"
            }
            public SquareFrame RandomCreat(int width_min, int width_max, int hight_min, int hight_max)
            {
                return new SquareFrame(ran.Next(width_min, width_max), ran.Next(hight_min, hight_max));
            }
            public SquareFrame RandomCreat()
            {
                return RandomCreat(6, 9, 6, 9);
            }
            public SquareFrame Print()
            {
                lattice_pointer = first_lattice;
                while (lattice_pointer != null)
                {
                    if (lattice_pointer.coord.x == width_0) lattice_pointer.PrintLine();
                    else lattice_pointer.Print();
                    lattice_pointer = lattice_pointer.next_lattice;
                }
                Console.WriteLine();
                return this;
            }
            public SquareFrame AddGivenPoint(float x, float y, MARK mark)
            {
                x -= DISPLAY_RESOLUTION_F;
                y -= DISPLAY_RESOLUTION_F;
                givenpoint_list.RemoveAll((item_l => item_l.x == x && item_l.y == y));
                givenpoint_list.Add(new Vector(x, y));
                if (lattice_dic.ContainsKey(new Vector(x, y)))
                {
                    lattice_dic[new Vector(x, y)].mark = mark;
                }
                return this;
            }
            public SquareFrame RandomAddPoint_Oval(
                float fixed_points_distances_min,
                float fixed_points_distances_max,
                float r_min,
                float r_max,
                float probability,
                MARK mark)
            {
                float r =
                    (float)ran.NextDouble()
                    + (r_max - r_min)
                    + r_min;
                float f_2 =
                    (float)ran.NextDouble()
                    * (fixed_points_distances_max - fixed_points_distances_min)
                    + fixed_points_distances_min;
                if (ran.Next(0, 1) > 0) f_2 *= -1;
                Vector f1 = new Vector((float)ran.NextDouble() * width_0, (float)ran.NextDouble() * height_0);
                Vector f2 = new Vector(f1.x + f_2, f1.y);
                foreach (var item in lattice_dic)
                {
                    if (((item.Key - f1).Length() + (item.Key - f2).Length()) < r * r)
                    {
                        if (givenpoint_list.Contains(item.Key))
                        {
                            givenpoint_list.RemoveAll((item_l => item_l == item.Key));
                        }
                        item.Value.mark = MARK.NULL;
                        if ((float)ran.NextDouble() < probability)
                        {
                            givenpoint_list.Add(item.Key);
                            item.Value.mark = mark;
                        }
                    }
                }
                return this;
            }
            public SquareFrame RandomAddPoint_Point(int number, MARK mark)
            {
                List<Vector> add_list = new List<Vector>();
                Vector ran_v = new Vector();
                while (number > 0)
                {
                    do
                    {
                        ran_v.x = (float)Math.Round(
                            ran.Next(0, (int)Math.Round(width_0 / DISPLAY_RESOLUTION_F))
                            * DISPLAY_RESOLUTION_F, 2);
                        ran_v.y = (float)Math.Round(
                            ran.Next(0, (int)Math.Round(height_0 / DISPLAY_RESOLUTION_F))
                            * DISPLAY_RESOLUTION_F, 2);
                    } while (add_list.Contains(ran_v));
                    add_list.Add(ran_v);
                    number--;
                }
                foreach (var item in add_list)
                {
                    givenpoint_list.RemoveAll((item_l => item_l == item));

                    if (lattice_dic.ContainsKey(item))
                    {
                        givenpoint_list.Add(item);
                        lattice_dic[item].mark = mark;
                    }
                }
                return this;
            }
            public Vector GetBezierPoint(float t, float ran_1, float ran_2)
            {
                Vector p_0 = new Vector(0f, 0f);
                Vector p_1 = p_0; p_1.y += 2 * ran_1 * height_0;
                Vector p_3 = new Vector(width_0, height_0);
                Vector p_2 = p_3; p_2.y -= 2 * ran_2 * height_0;
                Vector p_r = p_0 * (float)Math.Pow((1f - t), 3)
                    + p_1 * 3 * t * (float)Math.Pow((1f - t), 2)
                    + p_2 * 3 * (float)Math.Pow(t, 2) * (1f - t)
                    + p_3 * (float)Math.Pow(t, 3);
                return p_r;
            }
            public SquareFrame RandomAddPoint_Bezier(float p1_max, float p2_max, float probability)
            {
                p1_max *= (float)ran.NextDouble();
                p2_max *= (float)ran.NextDouble();
                givenpoint_list.Clear();
                foreach (var item in lattice_dic)
                {
                    item.Value.mark = MARK.NULL;
                    if (item.Key.y > GetBezierPoint(item.Key.x / width_0, p1_max, p2_max).y)
                    {
                        if (ran.NextDouble() < probability)
                        {
                            item.Value.mark = MARK.a;
                            givenpoint_list.Add(item.Key);
                        }
                    }
                    else
                    {
                        if (ran.NextDouble() < probability)
                        {
                            item.Value.mark = MARK.X;
                            givenpoint_list.Add(item.Key);
                        }
                    }
                }
                return this;
            }
            public SquareFrame Run_kNN(ushort k)
            {
                lattice_pointer = first_lattice;
                while (lattice_pointer != null)
                {
                    if (lattice_pointer.mark == MARK.NULL)
                    {
                        List<Vector> distance_list = new List<Vector>();
                        foreach (var item in givenpoint_list)
                        {
                            distance_list.Add(item - lattice_pointer.coord);
                        }
                        if (distance_list.Count() >= k)
                        {
                            distance_list.Sort();
                            Dictionary<MARK, uint> mark_num_dic = new Dictionary<MARK, uint>();
                            for (int i = k - 1; i >= 0; i--)
                            {
                                Lattice l_target = lattice_dic[lattice_pointer.coord + distance_list[i]];
                                if (mark_num_dic.ContainsKey(l_target.mark))
                                {
                                    mark_num_dic[l_target.mark]++;
                                }
                                else
                                {
                                    mark_num_dic.Add(l_target.mark, 1);
                                }
                            }
                            MARK mark_max = MARK.NULL;
                            uint mark_max_uint = 0;
                            foreach (var item in mark_num_dic)
                            {
                                if (item.Value >= mark_max_uint)
                                {
                                    mark_max_uint = item.Value;
                                    mark_max = item.Key;
                                }
                            }
                            lattice_pointer.mark = (MARK)((int)(mark_max) + 2);
                        }
                    }
                    lattice_pointer = lattice_pointer.next_lattice;
                }
                return this;
            }
        }
        struct Vector : IComparable<Vector>
        {
            public float x;
            public float y;
            public float length;
            public int ran_i;
            public float Length()
            {
                return (x * x) + (y * y);
            }
            public Vector(float x, float y)
            {
                this.x = (float)Math.Round(x, 2);
                this.y = (float)Math.Round(y, 2);
                length = (x * x) + (y * y);
                ran_i = new Random().Next();
            }
            public static bool operator ==(Vector v1, Vector v2)
            {
                if (v1.x == v2.x && v1.y == v2.y)
                    return true;
                return false;
            }
            public static bool operator !=(Vector v1, Vector v2)
            {
                if (v1.x != v2.x || v1.y != v2.y)
                    return true;
                return false;
            }
            public static Vector operator -(Vector v1, Vector v2)
            {
                return new Vector(
                    (float)Math.Round(v1.x - v2.x, 2)
                    , (float)Math.Round(v1.y - v2.y, 2));
            }
            public static Vector operator +(Vector v1, Vector v2)
            {
                return new Vector(
                    (float)Math.Round(v1.x + v2.x, 2)
                    , (float)Math.Round(v1.y + v2.y, 2));
            }
            public static Vector operator *(Vector v1, float f2)
            {
                return new Vector(
                    (float)Math.Round(v1.x * f2, 2)
                    , (float)Math.Round(v1.y * f2, 2));
            }
            public override string ToString()
            {
                return x.ToString() + "," + y.ToString();
            }
            public override int GetHashCode()
            {
                return ToString().GetHashCode();
            }
            public override bool Equals(object obj)
            {
                if (obj == null || GetType() != obj.GetType())
                    return false;
                Vector v2 = (Vector)obj;
                if (x == v2.x && y == v2.y) return true;
                else return false;
            }
            public int CompareTo(Vector other)
            {
                if (length > other.length)
                {
                    return 1;
                }
                else if (length == other.length)
                {
                    if (ran_i > other.ran_i)
                    {
                        return 1;
                    }
                    else if (ran_i == other.ran_i)
                    {
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    return -1;
                }
            }
        }

    }
}
