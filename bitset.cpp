
/*
bitset���壺bitset<size> bit;��bitset<maxn> bit;
bit[]����λ�洢����6=110��bit[0] = 0,bit[1] = 1,bit[2] = 1
��cout<<bit;��bit����λ���λ��������ճ����ֵ�д����ֻ����cout
bit�����������ַ�����(����char[],�÷���scanf�ĵ�ַһ��)��ʼ������bit(13),bit(string("11101"))
��λ��ֵ��bit[1] = 1,bit[1] = 0;
*/
/*bitset���ú���
����һ������bit��bitset��
bit.size()       ���ش�С��λ����
bit.count()     ����1�ĸ���
bit.any()       �����Ƿ���1
bit.none()      �����Ƿ�û��1
bit.set()       ȫ�����1
bit.set(p)      ����pλ���1��bitset�Ǵӵ�0λ��ʼ�ģ���
bit.set(p, x)   ����pλ���x
bit.reset()     ȫ�����0
bit.reset(p)    ����pλ���0
bit.flip()      ȫ��ȡ��
bit.flip(p)     ����pλȡ��
bit.to_ulong()  ������ת��Ϊunsigned long�Ľ�������������Χ�򱨴�
bit.to_ullong() ������ת��Ϊunsigned long long�Ľ�������������Χ�򱨴�
bit.to_string() ������ת��Ϊstring�Ľ��
