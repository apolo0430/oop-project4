#include "record.h";

Record::Record()
{
    // ������ �Ҹ� ������ ����
    pFormat.wFormatTag = WAVE_FORMAT_PCM;
    // �Ҹ� ä�� ��, 1�̸� ���, 2�̸� ���׷����Դϴ�.
    pFormat.nChannels = 2;
    // ���ø� ������ Ƚ��.
    // nSamplesPerSec���� 8.0 kHz, 11.025 kHz, 22.05 kHz, 44.1 kHz�� �ֽ��ϴ�.
    pFormat.nSamplesPerSec = 44100;
    // WAVE_FORMAT_PCM�̶�� �������̱� ������ nSamplesPerSec�� ���� ���̴�.
    pFormat.nAvgBytesPerSec = 44100;
    // 1ȸ ���ø��� ���Ǿ����� ������ ��Ʈ��, 8 �Ǵ� 16
    pFormat.wBitsPerSample = 16;
    // ���ø��� ���Ǵ� ����Ʈ ������ �޸� ũ��
    pFormat.nBlockAlign = pFormat.nChannels * (pFormat.wBitsPerSample / 8);
    // WAVE_FORMAT_PCM������ ���õǴ� ��
    pFormat.cbSize = 0;
    // waveInOpen�� �� ����ü�� ��ġ�� Open�ϴ� �Լ�.
    // �Ķ���ʹ� HWAVEIN, �ι�°�� ��ġ �����ε� ������ WAVE_MAPPER�� �־ �˴ϴ�.
    // ���� Ư���ϰ� ����ũ�� ������ �־(��Ʈ�� �⺻ ����ũ, �ص�� ����ũ) ���� ���߿� ������ ���ڸ� �����߽��ϴ�.
    // ����° �Ķ���ʹ� ���� ������ �ְ�, call�Լ��� �ֽ��ϴ�.
    // ������ �Ķ���ʹ� CALLBACK_FUNCTION�� �����ؼ� callback�Լ��� ����Ѵٴ� ���� �����մϴ�.
    if (waveInOpen(&hWaveIn, waveInGetNumDevs() - 1 /*WAVE_MAPPER*/, &pFormat, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION)) {
        // ���� �ܼ� ���
        cout << "Failed to open waveform input device." << endl;
        // ���� ����
        exit(0);
    }

    // ������ ����ü ����
    // ������ ���̸� �����Ѵ�. ������ 1�� ������ �����մϴ�.
    // �� ����ü���� ���ø��� 44100 ����Ʈ�� �߱� ������ �� ũ�⸦ �ִ´�.
    WaveInHdr.dwBufferLength = pFormat.nAvgBytesPerSec;
    // ���� �����͸� �Ҵ��Ѵ�.
    WaveInHdr.lpData = (char*)malloc(WaveInHdr.dwBufferLength);
    // ���̺귯������ ���� ������ ����� ���ϴ� �Լ�(����ڰ� ����ϴ� ���� �ƴ�)
    WaveInHdr.dwBytesRecorded = 0;
    // ���̺귯������ callback �Լ� ���� ���Ǵ� status flag
    WaveInHdr.dwFlags = 0;
    // �ݺ� ����� ���� (������� �ʴ´�.)
    WaveInHdr.dwLoops = 0;
    // ���� ����� ���� (������� �ʴ´�.)
    WaveInHdr.reserved = 0;
    // ���� ����. ���� ������ 1�� ������ �����Ͱ� �����µ�.. �����͸� ������ �ʿ䰡 �ִ�.
    // WaveInHdr.dwUser�� ���� ���۸� �����ϴ� ������ �ƴ�����, ������� �ʴ� �����̱� ������ ��Ȱ��
    WaveInHdr.dwUser = (ULONG_PTR)new BufferNode();
    bn = (BufferNode*)WaveInHdr.dwUser;
    // �������� �޸𸮸� ���Ҵ��ϱ� ������ 1byte�� �Ҵ�����
    bn->buffer = (char*)malloc(1);
    // �ʱ� ������ ���̴� 0�̴�.
    bn->length = 0;
}

Record::~Record()
{
    // ����ü�� �޸𸮴� ���� �Ҵ� �Ǿ��� ������ �����Ѵ�. ���̻� �ʿ䰡 ����.
    delete WaveInHdr.lpData;
    // ���� �Ҵ�� ���۸� �޸� �����Ѵ�.
    delete bn->buffer;
    delete bn;
}

void Record::rec()
{
    // ��ġ�� ���� �غ� �˸��� �Լ�
    if (waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR))) {
        // ���� �ܼ� ���
        cout << "waveInPrepareHeader error" << endl;
        // ��ġ �ݱ�
        waveInClose(hWaveIn);
        exit(0);
    }

    // ��ġ�� �޸𸮸� �Ҵ��� �ϴ� �Լ�
    if (waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR))) {
        // ���� �ܼ� ���
        cout << "waveInAddBuffer error" << endl;
        // ��ġ �ݱ�
        waveInClose(hWaveIn);
        exit(0);
    }

    // ���� ����
    if (waveInStart(hWaveIn)) {
        // ���� �ܼ� ���
        cout << "waveInStart error" << endl;
        // ��ġ �ݱ�
        waveInClose(hWaveIn);
        exit(0);
    }
    // �ܼ� ���
    cout << "Recording..." << endl;

    // �ƹ� Ű�� ������ ���͸� ġ�� ������ �ߴ��ϰ� �ٷ� ���Ϸ� �����Ѵ�.
    while (true) {
        cout << "If press any key, the record will save to the file." << endl;
        char input = -1;
        cin >> input;

        if (input != -1)
            break;
    }

    // callback�� ���Ḧ �˸��� Flag ����.
    WaveInHdr.dwFlags = WHDR_DONE;
    // ���� ����
    waveInStop(hWaveIn);
    // ��ġ�� ���� ������ �˸��� �Լ�
    waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    // ��ġ �ݱ�
    waveInClose(hWaveIn);
    // ������ �����͸� �����Ѵ�.
    WaveInHdr.dwBufferLength = bn->length;
    WaveInHdr.lpData = (char*)bn->buffer;
    // ������ �����Ѵ�.
    SaveWavFile("C:\Proj4\oop_proj4\record", &pFormat, &WaveInHdr);
}

void CALLBACK Record::waveInProc(HWAVEIN hWaveIn, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    switch (uMsg) { // �����Ͱ� ȣ��Ǹ� �޽����� WIM_DATA�� ȣ��ȴ�.
    case WIM_DATA:
        // ���� ������ ����ü ���
        WAVEHDR* WaveInHdr = (WAVEHDR*)dwParam1;
        // ���۸� �����´�.
        BufferNode* bn = (BufferNode*)WaveInHdr->dwUser;
        // WaveInHdr->dwBytesRecorded�� ������ �������̴�.
        // ������ �����ŭ �޸� ���Ҵ��� �Ѵ�.
        bn->buffer = realloc(bn->buffer, bn->length + WaveInHdr->dwBytesRecorded);
        // 1�� ������ ���ø��� ���� ������ ������ ������ ��ġ�� �� �ڿ� �޸� ���縦 �Ѵ�.
        // 1�ʿ��� bn->length�� 0�̱� ������ �״�� ������ 1�ʰ� memcpy��.
        // 2�ʿ��� bn->length�� 1���� ���̸�ŭ ���� ���� 1�� �ڿ� 1�ʰ� memcpy��.
        // 3�ʴ� 2�� �ڿ�...
        memcpy((char*)bn->buffer + bn->length, WaveInHdr->lpData, WaveInHdr->dwBytesRecorded);
        // ���̸� �÷��ش�.
        bn->length += WaveInHdr->dwBytesRecorded;

        // ��ġ�� ���� �غ� �˸��� �Լ�
        if (waveInPrepareHeader(hWaveIn, WaveInHdr, sizeof(WAVEHDR))) {
            // ���� �ܼ� ���
            cout << "waveInPrepareHeader error" << endl;
            // ��ġ �ݱ�
            waveInClose(hWaveIn);
            return;
        }

        // ��ġ�� �޸𸮸� �Ҵ��� �ϴ� �Լ�
        if (waveInAddBuffer(hWaveIn, WaveInHdr, sizeof(WAVEHDR))) {
            // ���� �ܼ� ���
            cout << "waveInPrepareHeader error" << endl;
            // ��ġ �ݱ�
            waveInClose(hWaveIn);
            return;
        }

        break;
    }
}

void Record::SaveWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
    // output stream�� �Ҵ�
    ofstream ostream;
    // ���� ����
    ostream.open(filename, fstream::binary);

    int subchunk1size = 16;
    int byteRate = format->nSamplesPerSec * format->nBlockAlign;
    int subchunk2size = WaveHeader->dwBufferLength * format->nChannels;
    int chunksize = (36 + subchunk2size);
    // wav���� ����ü��� �ۼ��Ѵ�.
    ostream.seekp(0, ios::beg);
    // chunk id
    ostream.write("RIFF", 4);
    // chunk size (36 + SubChunk2Size))
    ostream.write((char*)&chunksize, 4);
    // format
    ostream.write("WAVE", 4);
    // subchunk1ID
    ostream.write("fmt ", 4);
    // subchunk1size (������ PCM�̸� 16 ����)
    ostream.write((char*)&subchunk1size, 4);
    // AudioFormat (������ PCM�̸� 1 ����)
    ostream.write((char*)&format->wFormatTag, 2);
    // NumChannels
    ostream.write((char*)&format->nChannels, 2);
    // sample rate  
    ostream.write((char*)&format->nSamplesPerSec, 4);
    // byte rate (SampleRate * block align)
    ostream.write((char*)&byteRate, 4);
    // block align
    ostream.write((char*)&format->nBlockAlign, 2);
    // bits per sample
    ostream.write((char*)&format->wBitsPerSample, 2);
    // subchunk2ID
    ostream.write("data", 4);
    // subchunk2size (NumSamples * nBlockAlign)  
    ostream.write((char*)&subchunk2size, 4);
    // ���� ���� ������ �ۼ�  
    ostream.write(WaveHeader->lpData, WaveHeader->dwBufferLength);
    // ���� �ݱ�
    ostream.close();
}