char *resize(const char *str, unsigned size, unsigned new_size)
{
	char *buff = new char[new_size];
    unsigned s = size<new_size?size:new_size;
    
    for(unsigned i=0; i<s; ++i)
        buff[i] = str[i];
    
    delete[] str;
    return buff;
}


int main()
{
	char *buff =new char[100];
	buff = resize(buff, 100, 200);
	delete[] buff;


}
