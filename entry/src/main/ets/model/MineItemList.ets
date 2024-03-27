import { Component } from '@ohos.UiTest'
import url from '@ohos.url'
export interface InfoItem {
  id: string;
  title: string;//标题
  // show: Component; //点击后显示行为
  url:String
}

export const  MineItemList: InfoItem[] = [
  {
    id:'1',
    title:'修改个人资料',
    url:'MineShow'
  },
  {
    id:'2',
    title:'账号与安全',
    url:'AccountSecurity'

  },
  {
    id:'3',
    title:'检查更新',
    url:'UpdatesCheck'
  },
  {
    id:'4',
    title:'关于',
    url:'About'
  }
]