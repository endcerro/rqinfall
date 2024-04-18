
int N::operator-(N *this,N *param_1)
{
    return *(int *)(this + 104) - *(int *)(param_1 + 104);
}


int N::operator+(N *this,N *param_1)
{
    return *(int *)(param_1 + 104) + *(int *)(this + 104);
}

void N::setAnnotation(N *this,char *param_1)
{
    size_t n;

    n = strlen(param_1);
    memcpy(this + 4,param_1,__n);
    return;
}

void N::N(N *this,int param_1)

{
    *(undefined ***)this = &PTR_operator+_08048848;
    *(int *)(this + 0x68) = param_1;
    return;
}


void main(int ac, char** av)
{
    N *this;
    M *this_00;
    if (param_1 < 2) {
        _exit(1);
    }
    this = (N *)operator.new(0x6c);
    N::N(this,5);
    this_00 = (M *)operator.new(0x6c);
    N::N((N *)this_00,6);
    N::setAnnotation(this,av[1]);
    (** (code **) *this_00)(this_00,this);
    return;
}