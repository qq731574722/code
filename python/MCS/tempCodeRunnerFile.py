def sample(length):
    res = []
    interval = math.ceil(length/50)
    val = 0
    while val<=length:
        res.append(val)
        val+=interval
    return res
