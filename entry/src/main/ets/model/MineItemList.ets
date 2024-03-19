export interface InfoItem {
  id: string;
  title: string;//标题
  // icon?: Resource;//图标，可有可无
}

export const MineItemList: InfoItem[] = [
  {
    id:'1',
    title:'个人资料',
    // icon: $r('app.media.my_info')
  },
  {
    id:'2',
    title:'账号与安全',
    // icon: $r('app.media.zhanghuanquan')
  },
  {
    id:'3',
    title:'检查更新',
    // icon: $r('app.media.check_update')
  },
  {
    id:'4',
    title:'关于',
    // icon: $r('app.media.about')
  }

]